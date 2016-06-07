﻿#include "GLGraphicsAPI.h"

#include "../Platform/Platform.h"

#if GRAPHICS_API == OPENGL

#include "../Services/MemoryStack.h"
#include "../Alloc.h"

#include "OpenGL.h"
#include "../Math/Vector.h"

namespace photon
{
	GLGraphicsAPI::GLGraphicsAPI(GLAPIParam apiParam)
	{
		this->context = Platform::GLCreateContext(apiParam.createParam);
		auto result = glewInit();
		ASSERT(result == 0);
	}
	GLGraphicsAPI::~GLGraphicsAPI()
	{
		Platform::GLDestroyContext(context);
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
	void GLGraphicsAPI::ClearBuffer(const Vector& color)
	{
		glClearColor(color.x, color.y, color.z, color.w);
		glClearDepth(0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
	ShaderHandler GLGraphicsAPI::CreateShader(ShaderType type, const char* code)
	{
		GLenum shaderType;
		ShaderHandler handler;

		switch (type)
		{
		case ShaderType::VERTEX_SHADER: shaderType = GL_VERTEX_SHADER; break;
		case ShaderType::FRAGMENT_SHADER: shaderType = GL_FRAGMENT_SHADER; break;
		}

		handler.shader = glCreateShader(shaderType);
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
	ShaderProgramHandler GLGraphicsAPI::CreateShaderProgram(ShaderHandler* shaders, int count)
	{
		ShaderProgramHandler  handler;
		handler.program = glCreateProgram();

		for (int i = 0; i < count; ++i)
			glAttachShader(handler.program, shaders[i].shader);

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
	VertexBufferHandler GLGraphicsAPI::CreateVertexBuffer(const void* vertices, size_t verticesCount, int sizeOfVertex)
	{
		VertexBufferHandler handler;

		glGenBuffers(1, &handler.vb);
		glBindBuffer(GL_ARRAY_BUFFER, handler.vb);

		glBufferData(GL_ARRAY_BUFFER, sizeOfVertex * verticesCount, vertices, GL_STATIC_DRAW);

		return handler;
	}
	void GLGraphicsAPI::DestroyVertexBuffer(VertexBufferHandler vb)
	{
		glDeleteBuffers(1, &vb.vb);
	}
	VertexBufferBindingHandler GLGraphicsAPI::CreateVertexBufferBinding(const VertexBufferHandler* vertexBuffers, const VertexBufferLayout* layots, int buffersCount)
	{
		VertexBufferBindingHandler handler;

		glGenVertexArrays(1, &handler.vao);
		glBindVertexArray(handler.vao);

		for (int i = 0; i < buffersCount; ++i)
		{
			glBindBuffer(GL_ARRAY_BUFFER, vertexBuffers[i].vb);
			glEnableVertexAttribArray(i);

			int attrCount = layots[i].attributesCount;
			int offset = 0;


			for (int j = 0; j < attrCount; ++j)
			{
				VertexAttribute attr = layots[i].attributes[j];

				switch (attr.type)
				{
				case VertexParamType::FLOAT:
					glVertexAttribPointer(attr.location, 1, GL_FLOAT, GL_FALSE, sizeof(float), nullptr);
					break;
				case VertexParamType::FLOAT2:
					glVertexAttribPointer(attr.location, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, nullptr);
					break;
				case VertexParamType::FLOAT3:
					glVertexAttribPointer(attr.location, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, nullptr);
					break;
				case VertexParamType::FLOAT4:
					glVertexAttribPointer(attr.location, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 4, nullptr);
					break;
				default:
					break;
				}
			}
		}

		glBindVertexArray(GL_NONE);
		for (int i = 0; i < buffersCount; ++i)
			glDisableVertexAttribArray(i);

		return handler;
	}
	void GLGraphicsAPI::DestroyVertexBufferBinding(VertexBufferBindingHandler vbb)
	{
		glDeleteVertexArrays(1, &vbb.vao);
	}
	void GLGraphicsAPI::Draw(PrimitiveType type,  int indices)
	{
		glDrawArrays((uint32_t)type, 0, indices);
	}
	void GLGraphicsAPI::UseShaderProgram(ShaderProgramHandler program)
	{
		glUseProgram(program.program);
	}
	void GLGraphicsAPI::SetShaderProgramParam(uint32_t location, const Vector& val)
	{
		glUniform4fv(location, 1, &val.x);
	}
	void GLGraphicsAPI::UseVertexBufferBinding(VertexBufferBindingHandler vbb)
	{
		glBindVertexArray(vbb.vao);
	}
	void GLGraphicsAPI::ClearVertexBufferBinding()
	{
		glBindVertexArray(GL_NONE);
	}
}

#endif