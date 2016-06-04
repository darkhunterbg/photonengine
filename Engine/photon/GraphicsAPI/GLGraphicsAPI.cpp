#include "GLGraphicsAPI.h"

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
		glClear(GL_COLOR_BUFFER_BIT);
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
}

#endif