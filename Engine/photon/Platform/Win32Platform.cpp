#include "../Platform/Platform.h"

#if PLATFORM == WINDOWS

#define WIN32_LEAN_AND_MEAN

#include <Windows.h>

#include "Win32Platform.h"

namespace photon
{
	bool Win32Platfrom::initialized = false;

	void Win32Platfrom::Initialize()
	{
		ASSERT(!initialized);

		initialized = true;
	}
	void Win32Platfrom::Uninitialize()
	{
		ASSERT(initialized);
	}


	void* Win32Platfrom::MemoryAlloc(size_t size)
	{
		ASSERT(size > 0);

		return VirtualAlloc(nullptr, size, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
	}

	bool Win32Platfrom::MemoryFree(void* address, size_t size)
	{
		ASSERT(address);

		ASSERT(size > 0);

		return VirtualFree(address, size, MEM_RELEASE) == 0;
	}


	GLContext Win32Platfrom::GLCreateContext(GLCreateParam param)
	{
		GLContext result;

		PIXELFORMATDESCRIPTOR pfd = {};
		pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
		pfd.nVersion = 1;
		pfd.dwFlags = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW;
		pfd.iPixelType = PFD_TYPE_RGBA;
		pfd.cColorBits = 32;
		pfd.cDepthBits = 24;
		pfd.cAlphaBits = 8;
		pfd.iLayerType = PFD_MAIN_PLANE;

		result.hdc = GetWindowDC((HWND)param.hwindow);

		int pixelFormatIndex = ChoosePixelFormat((HDC)result.hdc, &pfd);
		SetPixelFormat((HDC)result.hdc, pixelFormatIndex, &pfd);

		result.hgldc = wglCreateContext((HDC)result.hdc);
		wglMakeCurrent((HDC)result.hdc, (HGLRC)result.hgldc);

		return result;
	}
	void Win32Platfrom::GLDestroyContext(GLContext context)
	{
		wglMakeCurrent(nullptr, (HGLRC)context.hgldc);
		wglDeleteContext((HGLRC)context.hgldc);
	}

	void Win32Platfrom::GLSwapBuffers(GLContext context)
	{
		SwapBuffers((HDC)context.hdc);
	}
}


#endif