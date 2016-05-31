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

	GLGraphicsAPI* GLGraphicsAPI::InitializeAPI(MemoryStack& stack, GraphicsAPIParam apiParam)
	{
		void* ptr = stack.Allocate(sizeof(GLGraphicsAPI));
		return new(ptr) GLGraphicsAPI(apiParam);
	}
	void GLGraphicsAPI::UninitializeAPI(GLGraphicsAPI* api)
	{
		Platform::GLDestroyContext(api->context);
	}

	void GLGraphicsAPI::SwapBuffers()
	{
		Platform::GLSwapBuffers(this->context);
	}
}

#endif