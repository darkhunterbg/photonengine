#include "Win32OpenGL.h"


#if (PLATFORM == WINDOWS)

#include "Win32Platform.h"
#include <Gl\gl.h>

namespace photon
{
	namespace platform
	{
		OpenGLContext CreateOpenGLContext(HWND window)
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

			HDC windowDC = GetWindowDC(window);

			int pixelFormatIndex = ChoosePixelFormat(windowDC, &pfd);
			SetPixelFormat(windowDC, pixelFormatIndex, &pfd);

			OpenGLContext context;
			context.dc = nullptr;
			context.handle = wglCreateContext(windowDC);

			ASSERT(context.handle);

			return context;
		}
		bool DeleteOpenGLContext(OpenGLContext& context)
		{
			return wglDeleteContext(context.handle);
		}
		bool SetCurrentOpenGLWindow(HWND windowHandle, OpenGLContext& context)
		{
			context.dc = GetWindowDC(windowHandle);
			return wglMakeCurrent(context.dc, context.handle);
		}

		bool SwapOpenGLBuffers(OpenGLContext& context)
		{
			return  SwapBuffers(context.dc);
		}
	}
}


#endif