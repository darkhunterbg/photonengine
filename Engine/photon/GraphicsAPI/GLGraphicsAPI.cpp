#include "GLGraphicsAPI.h"

#include "../Platform/Platform.h"

#if GRAPHICS_API == OPENGL

#include "../Services/MemoryStack.h"


namespace photon
{
	GLGraphicsAPI::GLGraphicsAPI(GLAPIParam apiParam)
	{
		this->context = Platform::GLCreateContext(apiParam.createParam);
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
}

#endif