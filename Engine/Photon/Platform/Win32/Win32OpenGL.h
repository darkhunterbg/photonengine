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
			HDC dc;
		};

		EXPORT OpenGLContext CreateOpenGLContext(HWND windowHandle);
		EXPORT bool DeleteOpenGLContext(OpenGLContext& context);
		EXPORT bool SetCurrentWindow(HWND windowHandle, OpenGLContext& context);
	
		EXPORT bool SwapOpenGLBuffers(OpenGLContext& context);
	}
}

#endif