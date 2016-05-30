#pragma once

#include "../PE.h"

#if defined( WINDOWS)

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include "../Services/MemoryStack.h"

namespace photon
{
	class EXPORT Win32Game
	{
		DISABLE_COPY(Win32Game);
	private:
		HINSTANCE hInstance;
		HWND hWindow;
		HGLRC hGlContext;
		HDC hDeviceContext;
		MemoryStack* memStack;

		bool startThreads = false;

		void Win32Init();
		void Win32Uninit();
		void CreateAndShowWindow();
		void CreateAndSetOpenGLContext();

		static DWORD WINAPI ThreadProc(LPVOID lpParameter);
		static LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	public:
		Win32Game(HINSTANCE hInstnace);
		virtual ~Win32Game() = 0;

		void Run();
	};
}
#endif