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
		VertexBufferHandler CreateVertexBuffer(const void* vertices, size_t verticesCount, int sizeOfVertex);
		void DestroyVertexBuffer(VertexBufferHandler vb);
		VertexBufferBindingHandler CreateVertexBufferBinding(const VertexBufferHandler* vertexBuffers, const VertexBufferLayout* layots, int buffersCount);
		void DestroyVertexBufferBinding(VertexBufferBindingHandler vbb);
		void Draw(PrimitiveType type, int indices);
		void UseShaderProgram(ShaderProgramHandler program);
		void SetShaderProgramParam(uint32_t location,const Vector& val);
		void UseVertexBufferBinding(VertexBufferBindingHandler vbb);
		void ClearVertexBufferBinding();

	} typedef GraphicsAPI;
}

#endif