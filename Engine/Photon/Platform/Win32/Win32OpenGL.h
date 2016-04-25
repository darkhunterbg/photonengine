#pragma once


#include "../../PE.h"


#if (PLATFORM == WINDOWS)

#include "Win32Platform.h"

namespace photon
{
	namespace platform
	{
		struct EXPORT OpenGLContext
		{
			HGLRC handle;
		};

		EXPORT OpenGLContext CreateOpenGLContext(HWND windowHandle);
		EXPORT bool DeleteOpenGLContext(OpenGLContext context);
	}
}

#endif