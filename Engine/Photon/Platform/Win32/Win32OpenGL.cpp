#include "Win32OpenGL.h"


#if (PLATFORM == WINDOWS)

#include "Win32Platform.h"
#include <Gl\gl.h>

namespace photon
{
	namespace platform
	{
		OpenGLContext CreateOpenGLContext(void* window)
		{
			PIXELFORMATDESCRIPTOR pfd = {};
			pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
			pfd.nVersion = 1;
			pfd.dwFlags = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW;
			pfd.iPixelType = PFD_TYPE_RGBA;
			pfd.cColorBits = 32;
			pfd.cDepthBits = 24;
			pfd.cAlphaBits = 8;
			pfd.iLayerType = PFD_MAIN_PLANE;

			HDC windowDC = GetWindowDC((HWND)window);

			int pixelFormatIndex = ChoosePixelFormat(windowDC, &pfd);
			SetPixelFormat(windowDC, pixelFormatIndex, &pfd);

			OpenGLContext context;
			context.handle = wglCreateContext(windowDC);

			return context;
		}
		bool DeleteOpenGLContext(OpenGLContext context)
		{
			return wglDeleteContext((HGLRC)context.handle);
		}
	}
}


#endif