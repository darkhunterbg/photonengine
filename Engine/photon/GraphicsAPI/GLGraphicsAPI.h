#pragma once

#include "../Macro.h"

#include "GraphicsAPI.h"

#if GRAPHICS_API == OPENGL

#include "../Platform/PlatformGL.h"
#include "GraphicsAPITypes.h"


namespace photon
{
	class MemoryStack;
	struct Vector;

	struct EXPORT GLAPIParam
	{
		GLCreateParam createParam;
	} typedef GraphicsAPIParam;

	class EXPORT GLGraphicsAPI
	{
		DISABLE_COPY(GLGraphicsAPI);

	private:
		GLContext context;
		GLGraphicsAPI(GLAPIParam apiParam);
		~GLGraphicsAPI();
	public:
		static GLGraphicsAPI* InitializeAPI(MemoryStack& stack, GraphicsAPIParam apiParam);
		static void UninitializeAPI(GLGraphicsAPI* api);

		void SwapBuffers();
		void ClearBuffer(const Vector&);

		ShaderHandler CreateShader(ShaderType type, const char* code);
		void DestroyShader(ShaderHandler shader);

		ShaderProgramHandler CreateShaderProgram(ShaderHandler* shaders, int count);
		void DestoryShaderProgram(ShaderProgramHandler shaderProgram);
		void UseShaderProgram(ShaderProgramHandler program);

		VertexBufferHandler CreateVertexBuffer(const void* vertices, size_t verticesCount, int sizeOfVertex);
		void DestroyVertexBuffer(VertexBufferHandler vb);

		VertexBufferBindingHandler CreateVertexBufferBinding(const VertexBufferHandler* vertexBuffers, const VertexBufferLayout* layots, int buffersCount);
		void DestroyVertexBufferBinding(VertexBufferBindingHandler vbb);
		void UseVertexBufferBinding(VertexBufferBindingHandler vbb);
		void ClearVertexBufferBinding();

		UniformBufferHandler CreateUniformBuffer(size_t bufferSize, void* bufferValue);
		void DestroyUniformBuffer(UniformBufferHandler handler);
		void* StartUpdateUniformBuffer(UniformBufferHandler handler);
		void EndUpdateUniformBuffer();

		void BindBufferToProgramBlock(ShaderProgramHandler handler, const char* blockName, UniformBufferHandler buffer);

		void Draw(PrimitiveType type, int indices);



	} typedef GraphicsAPI;
}

#endif