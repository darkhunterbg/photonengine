#pragma once

#include "../Macro.h"

#include "GraphicsAPI.h"

#if GRAPHICS_API == OPENGL

#include "../Platform/PlatformGL.h"
#include "GraphicsAPITypes.h"
#include "../Utils/Array.h"
#include "GLPrivate.h"

namespace photon
{
	class MemoryStack;
	struct Vector4;
	struct Matrix;

	struct EXPORT GLAPIParam
	{
		GLCreateParam createParam;
	} typedef GraphicsAPIParam;

	class EXPORT GLGraphicsAPI
	{
		DISABLE_COPY(GLGraphicsAPI);

	private:
		GLContext context;

		static const int MAX_STATES = 16;
		Array<gl::GLDepthStencilState, MAX_STATES> depthStencilStates;
		Array<gl::GLRasterizationState, MAX_STATES> rasterizationStates;
		Array<gl::GLBlendingState, MAX_STATES> blendStates;

		GLGraphicsAPI(GLAPIParam apiParam);
		~GLGraphicsAPI();
	public:
		static GLGraphicsAPI* InitializeAPI(MemoryStack& stack, GraphicsAPIParam apiParam);
		static void UninitializeAPI(GLGraphicsAPI* api);

		void GetVersion(char* outBuffer,int bufferSize);
		void GetDeviceName(char* outBuffer, int bufferSize);

		void SwapBuffers();
		void ClearFrameBuffer(const Vector4& color, float depth);

		ShaderHandler CreateShader(ShaderType type, const char* code);
		void DestroyShader(ShaderHandler shader);

		ShaderProgramHandler CreateShaderProgram(const ShaderHandler* shaders, int count);
		void DestoryShaderProgram(ShaderProgramHandler shaderProgram);
		void UseShaderProgram(ShaderProgramHandler program);

		VertexBufferHandler CreateVertexBuffer(VertexBufferType type, const void* vertices, size_t verticesCount, int sizeOfVertex);
		void DestroyVertexBuffer(VertexBufferHandler vb);
		void* StartUpdateVertexBuffer(VertexBufferHandler handler);
		void EndUpdateVertexBuffer();

		VertexBufferBindingHandler CreateVertexBufferBinding(const VertexBufferHandler* vertexBuffers, const VertexBufferLayout* layots, int buffersCount, IndexBufferHandler indexBuffer = IndexBufferHandler::Empty);
		void DestroyVertexBufferBinding(VertexBufferBindingHandler vbb);
		void UseVertexBufferBinding(VertexBufferBindingHandler vbb);
		void ClearVertexBufferBinding();

		UniformBufferHandler CreateUniformBuffer(size_t bufferSize, void* bufferValue);
		void DestroyUniformBuffer(UniformBufferHandler handler);
		void* StartUpdateUniformBuffer(UniformBufferHandler handler);
		void EndUpdateUniformBuffer();

		IndexBufferHandler CreateIndexBuffer(const void* indices, size_t indicesCount, IndiceType indiceType);
		void DestroyIndexBuffer(IndexBufferHandler handler);

		void BindBufferToProgramBlock(ShaderProgramHandler handler, const char* blockName, uint32_t bindPoint, UniformBufferHandler buffer);
		void UseUniformBuffer(UniformBufferHandler buffer, uint32_t bindPoint);

		void Draw(PrimitiveType type, unsigned int elemCount);
		void DrawIndexed(PrimitiveType pType, IndiceType iType, uint32_t elemCount);
		void DrawIndexedInstanced(PrimitiveType pType, IndiceType iType, uint32_t elemCount, uint32_t instancesCount);

		TextureHandler LoadTextureBitmap(void* data);
		TextureHandler LoadTextureDDS(void* data);
		void DestroyTexture(TextureHandler handler);
		void UseTexture(TextureHandler texture, uint32_t textureUnit, uint32_t samplerLocation);

		RasterizationStateHandler CreateRasterizationState(FillMode fillMode, CullMode cullMode);
		void DestroyRasterizationState(RasterizationStateHandler handler);
		void SetRasterizationState(RasterizationStateHandler state);

		BlendStateHandler CreateBlendState(bool enabled, BlendFactor source, BlendFactor dest);
		void DestroyBlendState(BlendStateHandler handler);
		void SetBlendState(BlendStateHandler state);

		DepthStencilStateHandler CreateDepthStencilState(bool depthEnabled);
		void DestroyDepthStencilState(DepthStencilStateHandler handler);
		void SetDepthStencilState(DepthStencilStateHandler state);

		SamplerHandler CreateSampler(MinMagFilter minFilter, MinMagFilter magFilter, float maxAnisotropy);
		void DestroySampler(SamplerHandler handler);
		void SetTextureUnitSampler(uint32_t textureUnit, SamplerHandler handler);
		void ClearTextureUnitSampler(uint32_t textureUnit);
		int GetProgramSamplerLocation(ShaderProgramHandler handler, const char* samplerName);

		void SetViewport(Viewport viewport);


	} typedef GraphicsAPI;
}

#endif