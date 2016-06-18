#include "GLGraphicsAPI.h"

#include "../Platform/Platform.h"


#if GRAPHICS_API == OPENGL

#include "../Services/MemoryStack.h"
#include "../Alloc.h"
#include "../Text.h"

#include "OpenGL.h"

#include <cstdio>


#include "../Math/Vector.h"
#include "../Math/Matrix.h"


namespace photon
{
	void CheckForErrors(const char* method)
	{
		uint32_t error = glGetError();
		ASSERT(error == GL_NONE);
	}



	GLGraphicsAPI::GLGraphicsAPI(GLAPIParam apiParam)
	{
		this->context = Platform::GLCreateContext(apiParam.createParam);
		auto error = glewInit();
		ASSERT(error == GL_NONE);
	}
	GLGraphicsAPI::~GLGraphicsAPI()
	{
		Platform::GLDestroyContext(context);
	}

	void GLGraphicsAPI::GetVersion(char* outBuffer, int bufferSize)
	{
		const char* version = (const char*)glGetString(GL_VERSION);
		const char* vendor = (const char*)glGetString(GL_VENDOR);

		sprintf_s(outBuffer, bufferSize, "%s OpenGL %s", vendor, version);
	}
	void GLGraphicsAPI::GetDeviceName(char* outBuffer, int bufferSize)
	{
		const char* renderer = (const char*)glGetString(GL_RENDERER);

		sprintf_s(outBuffer, bufferSize, renderer);
	}

	GLGraphicsAPI* GLGraphicsAPI::InitializeAPI(MemoryStack& stack, GraphicsAPIParam apiParam)
	{
		return  MEM_NEW(stack, GLGraphicsAPI)(apiParam);

	}
	void GLGraphicsAPI::UninitializeAPI(GLGraphicsAPI* api)
	{
		api->~GLGraphicsAPI();
	}

	void GLGraphicsAPI::SwapBuffers()
	{
		Platform::GLSwapBuffers(this->context);
	}
	void GLGraphicsAPI::ClearFrameBuffer(const Vector4& color, float depth)
	{
		glClearColor(color.x, color.y, color.z, color.w);
		glClearDepth(depth);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		CheckForErrors("glClear");
	}
	ShaderHandler GLGraphicsAPI::CreateShader(ShaderType type, const char* code)
	{
		ShaderHandler handler;

		handler.shader = glCreateShader((uint32_t)type);
		glShaderSource(handler.shader, 1, &code, nullptr);
		glCompileShader(handler.shader);

		GLint success = 0;
		glGetShaderiv(handler.shader, GL_COMPILE_STATUS, &success);

		if (success == GL_FALSE)
		{
			char error[4096];
			glGetShaderInfoLog(handler.shader, 4096, nullptr, error);
			ASSERT(false);
		}

		return handler;
	}
	void GLGraphicsAPI::DestroyShader(ShaderHandler handler)
	{
		glDeleteShader(handler.shader);
	}
	ShaderProgramHandler GLGraphicsAPI::CreateShaderProgram(const ShaderHandler* shaders, int count)
	{
		ShaderProgramHandler  handler;
		handler.program = glCreateProgram();

		for (int i = 0; i < count; ++i)
		{
			glAttachShader(handler.program, shaders[i].shader);
			CheckForErrors("glAttachShader");
		}

		glLinkProgram(handler.program);


		GLint linked;
		glGetProgramiv(handler.program, GL_LINK_STATUS, &linked);
		if (linked == GL_FALSE)
		{
			char error[4096];
			glGetProgramInfoLog(handler.program, 4096, nullptr, error);
			ASSERT(false);
		}

		for (int i = 0; i < count; ++i)
			glDetachShader(handler.program, shaders[i].shader);

		return handler;
	}
	void GLGraphicsAPI::DestoryShaderProgram(ShaderProgramHandler shaderProgram)
	{
		glDeleteProgram(shaderProgram.program);
	}
	VertexBufferHandler GLGraphicsAPI::CreateVertexBuffer(VertexBufferType type, const void* vertices, size_t verticesCount, int sizeOfVertex)
	{
		VertexBufferHandler handler;

		glGenBuffers(1, &handler.vb);
		glBindBuffer(GL_ARRAY_BUFFER, handler.vb);
		glBufferData(GL_ARRAY_BUFFER, sizeOfVertex * verticesCount, vertices, (uint32_t)type);
		CheckForErrors("glBufferData");
		glBindBuffer(GL_ARRAY_BUFFER, GL_NONE);

		return handler;
	}
	void GLGraphicsAPI::DestroyVertexBuffer(VertexBufferHandler vb)
	{
		glDeleteBuffers(1, &vb.vb);
	}
	void* GLGraphicsAPI::StartUpdateVertexBuffer(VertexBufferHandler handler)
	{
		glBindBuffer(GL_ARRAY_BUFFER, handler.vb);
		void* ptr = glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
		CheckForErrors("glMapBuffer");
		return ptr;
	}
	void GLGraphicsAPI::EndUpdateVertexBuffer()
	{
		glUnmapBuffer(GL_ARRAY_BUFFER);
		glBindBuffer(GL_ARRAY_BUFFER, GL_NONE);
	}

	VertexBufferBindingHandler GLGraphicsAPI::CreateVertexBufferBinding(const VertexBufferHandler* vertexBuffers, const VertexBufferLayout* layots, int buffersCount, IndexBufferHandler indexBuffer)
	{
		VertexBufferBindingHandler handler;

		glGenVertexArrays(1, &handler.vao);
		glBindVertexArray(handler.vao);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer.ib);
		CheckForErrors("glBindBuffer");

		for (int i = 0; i < buffersCount; ++i)
		{
			glBindBuffer(GL_ARRAY_BUFFER, vertexBuffers[i].vb);
			CheckForErrors("glBindBuffer");

			int attrCount = layots[i].attributesCount;
			int offset = 0;

			size_t layoutSize = layots[i].GetTotalSize();

			char* ptr = 0;

			for (int j = 0; j < attrCount; ++j)
			{
				VertexAttribute attr = layots[i].attributes[j];
				int size = 0;

				glEnableVertexAttribArray(attr.location);
				CheckForErrors("glEnableVertexAttribArray");

				switch (attr.type)
				{
				case VertexParamType::FLOAT:
					size = sizeof(float);
					glVertexAttribPointer(attr.location, 1, GL_FLOAT, GL_FALSE, layoutSize, ptr);
					break;
				case VertexParamType::FLOAT2:
					size = sizeof(float) * 2;
					glVertexAttribPointer(attr.location, 2, GL_FLOAT, GL_FALSE, layoutSize, ptr);
					break;
				case VertexParamType::FLOAT3:
					size = sizeof(float) * 3;
					glVertexAttribPointer(attr.location, 3, GL_FLOAT, GL_FALSE, layoutSize, ptr);
					break;
				case VertexParamType::FLOAT4:
					size = sizeof(float) * 4;
					glVertexAttribPointer(attr.location, 4, GL_FLOAT, GL_FALSE, layoutSize, ptr);
					break;
				default:
					break;
				}

				CheckForErrors("glVertexAttribPointer");

				glVertexAttribDivisor(attr.location, layots[i].instance);
				CheckForErrors("glVertexAttribDivisor");

				ptr += size;
			}
		}

		glBindVertexArray(GL_NONE);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_NONE);
		glBindBuffer(GL_ARRAY_BUFFER, GL_NONE);

		for (int i = 0; i < buffersCount; ++i)
		{
			int attrCount = layots[i].attributesCount;
			for (int j = 0; j < attrCount; ++j)
			{
				VertexAttribute attr = layots[i].attributes[j];
				glDisableVertexAttribArray(attr.location);
			}

		}


		return handler;
	}
	void GLGraphicsAPI::DestroyVertexBufferBinding(VertexBufferBindingHandler vbb)
	{
		glDeleteVertexArrays(1, &vbb.vao);
	}

	void GLGraphicsAPI::Draw(PrimitiveType type, unsigned int elemCount)
	{
		glDrawArrays((uint32_t)type, 0, elemCount);
		CheckForErrors("glDrawArrays");
	}
	void GLGraphicsAPI::DrawIndexed(PrimitiveType pType, IndiceType iType, uint32_t elemCount)
	{
		glDrawElements((uint32_t)(pType), elemCount, (uint32_t)iType, 0);
		CheckForErrors("glDrawElements");
	}
	void GLGraphicsAPI::DrawIndexedInstanced(PrimitiveType pType, IndiceType iType, uint32_t elemCount, uint32_t instancesCount)
	{
		glDrawElementsInstanced((uint32_t)(pType), elemCount, (uint32_t)iType, 0, instancesCount);
		CheckForErrors("glDrawElementsInstanced");
	}

	void GLGraphicsAPI::UseShaderProgram(ShaderProgramHandler program)
	{
		glUseProgram(program.program);
		CheckForErrors("glUseProgram");
	}

	void GLGraphicsAPI::UseVertexBufferBinding(VertexBufferBindingHandler vbb)
	{
		glBindVertexArray(vbb.vao);
		CheckForErrors("glBindVertexArray");
	}
	void GLGraphicsAPI::ClearVertexBufferBinding()
	{
		glBindVertexArray(GL_NONE);
	}
	void* GLGraphicsAPI::StartUpdateUniformBuffer(UniformBufferHandler block)
	{
		glBindBuffer(GL_UNIFORM_BUFFER, block.ub);
		void* ptr = glMapBuffer(GL_UNIFORM_BUFFER, GL_WRITE_ONLY);
		CheckForErrors("glMapBuffer");
		return ptr;
	}
	void GLGraphicsAPI::EndUpdateUniformBuffer()
	{
		glUnmapBuffer(GL_UNIFORM_BUFFER);
		glBindBuffer(GL_UNIFORM_BUFFER, GL_NONE);
	}
	UniformBufferHandler GLGraphicsAPI::CreateUniformBuffer(size_t bufferSize, void* bufferValue)
	{
		UniformBufferHandler handler;

		glGenBuffers(1, &handler.ub);
		glBindBuffer(GL_UNIFORM_BUFFER, handler.ub);
		glBufferData(GL_UNIFORM_BUFFER, bufferSize, bufferValue, GL_DYNAMIC_DRAW);
		CheckForErrors("glBufferData");
		glBindBuffer(GL_UNIFORM_BUFFER, GL_NONE);

		return handler;
	}
	void GLGraphicsAPI::DestroyUniformBuffer(UniformBufferHandler buffer)
	{
		glDeleteBuffers(1, &buffer.ub);
	}
	void GLGraphicsAPI::BindBufferToProgramBlock(ShaderProgramHandler program, const char* blockName, uint32_t bindPoint, UniformBufferHandler buffer)
	{
		uint32_t blockIndex = glGetUniformBlockIndex(program.program, blockName);
		CheckForErrors("glGetUniformBlockIndex");

		glUniformBlockBinding(program.program, blockIndex, bindPoint);
		CheckForErrors("glUniformBlockBinding");
	}
	void GLGraphicsAPI::UseUniformBuffer(UniformBufferHandler buffer, uint32_t bindPoint)
	{
		glBindBufferBase(GL_UNIFORM_BUFFER, bindPoint, buffer.ub);
		CheckForErrors("glBindBufferBase");
	}


	IndexBufferHandler GLGraphicsAPI::CreateIndexBuffer(const void* indices, size_t indicesCount, IndiceType indiceType)
	{
		IndexBufferHandler handler;

		size_t size;
		switch (indiceType)
		{
		case IndiceType::UINT: size = sizeof(uint32_t); break;
		case IndiceType::USHORT: size = sizeof(uint16_t); break;
		default:
			break;
		}

		glGenBuffers(1, &handler.ib);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, handler.ib);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesCount* size, indices, GL_STATIC_DRAW);
		CheckForErrors("glBufferData");
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_NONE);

		return handler;
	}
	void GLGraphicsAPI::DestroyIndexBuffer(IndexBufferHandler handler)
	{
		glDeleteBuffers(1, &handler.ib);
	}

	TextureHandler GLGraphicsAPI::LoadTextureDDS(void* data)
	{
		TextureHandler handler;

		BYTE* header = (BYTE*)data + 4;
		BYTE* buffer = header + 124;

		/* verify the type of file */
		char* filecode = (char*)data;
		ASSERT(text::Compare(filecode, "DDS "));

		uint32_t height = *(uint32_t*)&(header[8]);
		uint32_t width = *(uint32_t*)&(header[12]);
		uint32_t linearSize = *(uint32_t*)&(header[16]);
		uint32_t mipMapCount = *(uint32_t*)&(header[24]);
		gl::FourCCType fourCC = *(gl::FourCCType*)&(header[80]);

		uint32_t bufsize;
		uint32_t blockSize = (fourCC == gl::FourCCType::FOURCC_DXT1) ? 8 : 16;
		int numblocks = ((width + 3) / 4) * ((height + 3) / 4);   // number of 4*4 texel blocks

																  /* how big is it going to be including all mipmaps? */
		if (linearSize != 0)
			bufsize = mipMapCount > 1 ? linearSize * 2 : linearSize;
		else
			bufsize = blockSize * numblocks;

		if (mipMapCount < 1)
			mipMapCount = 1;


		uint32_t components = (fourCC == gl::FourCCType::FOURCC_DXT1) ? 3 : 4;
		uint32_t format;
		switch (fourCC)
		{
		case  gl::FourCCType::FOURCC_DXT1:
			format = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
			break;
		case  gl::FourCCType::FOURCC_DXT3:
			format = GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;
			break;
		case  gl::FourCCType::FOURCC_DXT5:
			format = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
			break;
		default:
			ASSERT(false);
		}

		glGenTextures(1, &handler.texture);

		// "Bind" the newly created texture : all future texture functions will modify this texture
		glBindTexture(GL_TEXTURE_2D, handler.texture);
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

		//Filtering
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

		UINT offset = 0;

		/* load the mipmaps */
		for (UINT level = 0; level < mipMapCount && (width || height); ++level)
		{
			UINT size = ((width + 3) / 4)*((height + 3) / 4)*blockSize;
			//UINT size = ((width ) / 4)*((height) / 4)*blockSize;
			glCompressedTexImage2D(GL_TEXTURE_2D, level, format, width, height, 0, size, buffer + offset);

			CheckForErrors("glCompressedTexImage2D");

			offset += size;
			width = max(width / 2, 1);
			height = max(height / 2, 1);
		}
		if (mipMapCount == 0)
		{
			glGenerateTextureMipmap(handler.texture);
			CheckForErrors("glGenerateTextureMipmap");
		}

		glBindTexture(GL_TEXTURE_2D, GL_NONE);

		return handler;
	}
	TextureHandler GLGraphicsAPI::LoadTextureBitmap(void* data)
	{
		// Create one OpenGL texture
		TextureHandler handler;

		BYTE* header = (BYTE*)data;  // Each BMP file begins by a 54-bytes header
		uint32_t dataPos;     // Position in the file where the actual data begins
		uint32_t width, height;
		uint32_t imageSize;   // = width*height*3
								  // Actual RGB data

		ASSERT(header[0] == 'B' && header[1] == 'M');

		dataPos = *(int*)&(header[0x0A]);
		imageSize = *(int*)&(header[0x22]);
		width = *(int*)&(header[0x12]);
		height = *(int*)&(header[0x16]);

		// Some BMP files are misformatted, guess missing information
		if (imageSize == 0)    imageSize = width*height * 3; // 3 : one byte for each Red, Green and Blue component
		if (dataPos == 0)      dataPos = 54; // The BMP header is done that way

		BYTE* buffer = header + 54;

		glGenTextures(1, &handler.texture);
		glBindTexture(GL_TEXTURE_2D, handler.texture);

		// Give the image to OpenGL
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, buffer);
		CheckForErrors("glTexImage2D");

		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

		glGenerateTextureMipmap(handler.texture);
		CheckForErrors("glGenerateTextureMipmap");

		glBindTexture(GL_TEXTURE_2D, GL_NONE);

		return handler;
	}

	void GLGraphicsAPI::DestroyTexture(TextureHandler handler)
	{
		glDeleteTextures(1, &handler.texture);
	}
	void GLGraphicsAPI::UseTexture(TextureHandler texture, uint32_t textureUnit, uint32_t samplerLocation)
	{
		glUniform1i(samplerLocation, textureUnit);
		CheckForErrors("glUniform1i");

		glActiveTexture(GL_TEXTURE0 + textureUnit);
		CheckForErrors("glActiveTexture");

		glBindTexture(GL_TEXTURE_2D, texture.texture);

	}

	RasterizationStateHandler GLGraphicsAPI::CreateRasterizationState(FillMode fillMode, CullMode cullMode)
	{
		RasterizationStateHandler handler;

		rasterizationStates.Add({ fillMode,cullMode });
		handler.id = rasterizationStates.Count();

		return handler;
	}
	void GLGraphicsAPI::DestroyRasterizationState(RasterizationStateHandler handler)
	{
		rasterizationStates.Remove(handler.id - 1);
	}
	void GLGraphicsAPI::SetRasterizationState(RasterizationStateHandler handler)
	{
		gl::GLRasterizationState& state = rasterizationStates[handler.id - 1];

		if (state.cullMode != CullMode::NONE)
		{
			glEnable(GL_CULL_FACE);
			glCullFace((uint32_t)state.cullMode);
		}
		else
		{
			glDisable(GL_CULL_FACE);
			return;
		}

		glPolygonMode(GL_FRONT_AND_BACK, (uint32_t)state.fillMode);
		CheckForErrors("glPolygonMode");

	}

	BlendStateHandler GLGraphicsAPI::CreateBlendState(bool enabled, BlendFactor source, BlendFactor dest)
	{
		BlendStateHandler handler;

		blendStates.Add({ source,dest,enabled });
		handler.id = blendStates.Count();

		return handler;
	}
	void GLGraphicsAPI::DestroyBlendState(BlendStateHandler handler)
	{
		blendStates.Remove(handler.id - 1);
	}
	void GLGraphicsAPI::SetBlendState(BlendStateHandler handler)
	{
		gl::GLBlendingState& state = blendStates[handler.id - 1];

		if (state.enabled)
		{
			glEnable(GL_BLEND);
			glBlendFunc((uint32_t)state.source, (uint32_t)state.dest);
		}
		else
		{
			glDisable(GL_BLEND);
		}
	}

	DepthStencilStateHandler GLGraphicsAPI::CreateDepthStencilState(bool depthEnabled)
	{
		DepthStencilStateHandler handler;

		depthStencilStates.Add({ depthEnabled });
		handler.id = depthStencilStates.Count();

		return handler;
	}
	void GLGraphicsAPI::DestroyDepthStencilState(DepthStencilStateHandler handler)
	{
		depthStencilStates.Remove(handler.id - 1);
	}
	void GLGraphicsAPI::SetDepthStencilState(DepthStencilStateHandler handler)
	{
		gl::GLDepthStencilState& state = depthStencilStates[handler.id - 1];

		if (state.depthEnabled)
		{
			glEnable(GL_DEPTH_TEST);
			glDepthMask(GL_TRUE);
		}
		else
		{
			glDisable(GL_DEPTH_TEST);
		}

	}

	SamplerHandler GLGraphicsAPI::CreateSampler(MinMagFilter minFilter, MinMagFilter magFilter, float maxAnisotropy)
	{
		SamplerHandler sampler;
		glGenSamplers(1, &sampler.id);

		glSamplerParameteri(sampler.id, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		CheckForErrors("glSamplerParameteri");
		glSamplerParameteri(sampler.id, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		CheckForErrors("glSamplerParameteri");
		glSamplerParameteri(sampler.id, GL_TEXTURE_MAG_FILTER, (uint32_t)magFilter);
		CheckForErrors("glSamplerParameteri");
		glSamplerParameteri(sampler.id, GL_TEXTURE_MIN_FILTER, (uint32_t)minFilter);
		CheckForErrors("glSamplerParameteri");
		glSamplerParameterf(sampler.id, GL_TEXTURE_MAX_ANISOTROPY_EXT, maxAnisotropy);
		CheckForErrors("glSamplerParameterf");

		return sampler;
	}
	void GLGraphicsAPI::DestroySampler(SamplerHandler handler)
	{
		glDeleteSamplers(1, &handler.id);


	}
	int GLGraphicsAPI::GetProgramSamplerLocation(ShaderProgramHandler handler, const char* samplerName)
	{
		return  glGetUniformLocation(handler.program, samplerName);
	}
	void GLGraphicsAPI::SetTextureUnitSampler(uint32_t textureUnit, SamplerHandler handler)
	{
		glBindSampler(textureUnit, handler.id);
	}
	void GLGraphicsAPI::ClearTextureUnitSampler(uint32_t textureUnit)
	{
		glBindSampler(textureUnit, GL_NONE);
	}

	void GLGraphicsAPI::SetViewport(Viewport viewport)
	{
		glViewport(viewport.x, viewport.y, viewport.width, viewport.height);
		CheckForErrors("glViewport");
	}

}

#endif