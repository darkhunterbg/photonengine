#include "GLGraphicsAPI.h"

#include "../Platform.h"

#if defined (OPENGL)

namespace photon
{
	GLGraphicsAPI::GLGraphicsAPI(const GLAPIParam* apiParam)
		:GraphicsAPI(GraphicsAPIType::OpenGL)
	{
		this->context = Platform::GLCreateContext(apiParam->createParam);
	}

	GLGraphicsAPI::~GLGraphicsAPI()
	{
		Platform::GLDestroyContext(context);
	}

	void GLGraphicsAPI::SwapBuffers()
	{
		Platform::GLSwapBuffers(this->context);
	}
}

#endif