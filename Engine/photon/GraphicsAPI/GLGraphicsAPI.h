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

	} typedef GraphicsAPI;
}

#endif