#pragma once

#include "../PE.h"

#if (PLATFORM == WINDOWS)

#include "Win32Game.h"

#include "../Graphics/GraphicsService.h"
#include "../Memory/MemoryService.h"
#include "../Job/JobService.h"

#include "../Platform/Win32Platform.h"


#include <gl\GL.h>


namespace photon
{
	namespace platform
	{
		Win32Game::Win32Game(HINSTANCE hInstance)
		{
			this->hInstance = hInstance;
			Win32Init();
		}

		Win32Game::~Win32Game()
		{
			Win32Uninit();
		}

		void Win32Game::Run()
		{

			MSG msg;

			LONGLONG deltaTime = 0;
			LARGE_INTEGER time;
			QueryPerformanceCounter(&time);
			LARGE_INTEGER freq;
			QueryPerformanceFrequency(&freq);

			while (true)
			{
				while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
				{
					TranslateMessage(&msg);
					DispatchMessage(&msg);
				}

				if (msg.message == WM_QUIT)
					break;

				LARGE_INTEGER time1;
				QueryPerformanceCounter(&time1);
				LONGLONG delta = time1.QuadPart - time.QuadPart;
				time = time1;
				deltaTime += delta;

				LONGLONG  deltaMcS = ((1000 * 1000 * deltaTime) / freq.QuadPart);
				if (deltaMcS >= 16'666)
				{
					//================ GAME LOOP ============================
					SwapBuffers(hDeviceContext);
					//======================================================
					glClear(GL_COLOR_BUFFER_BIT);
					deltaTime -= ((freq.QuadPart * 16'666) / (1000 * 1000));
				}

			}
		}

		void Win32Game::Win32Init()
		{
			CreateAndShowWindow();
			CreateAndSetOpenGLContext();

			photon::platform::Win32Platfrom::Initialize();

			photon::memory::MemoryService::Initialize();
			void* memory = photon::gl_MemoryService->AllocatePage(Megabytes(1));
			memStack = photon::memory::MemoryStack::New(memory, Megabytes(1));

			HANDLE thread = CreateThread(nullptr, 0, Win32Game::ThreadProc, this, CREATE_SUSPENDED, nullptr);
			photon::job::JobService::Initialize(*memStack, 1);
			ResumeThread(thread);

			photon::graphics::GraphicsService::Initialize(*memStack);
		}
		void Win32Game::Win32Uninit()
		{
			photon::graphics::GraphicsService::Uninitialize();
			photon::job::JobService::Uninitialize();

			memStack->Clear();
			photon::memory::MemoryService::Uninitialize();
			photon::platform::Win32Platfrom::Uninitialize();

			wglMakeCurrent(nullptr, hGlContext);
			wglDeleteContext(hGlContext);

			DestroyWindow(hWindow);
		}
		void Win32Game::CreateAndShowWindow()
		{
			WNDCLASSEX wc;

			ZeroMemory(&wc, sizeof(WNDCLASSEX));

			wc.cbSize = sizeof(WNDCLASSEX);
			wc.style = CS_HREDRAW | CS_VREDRAW;
			wc.lpfnWndProc = WindowProc;
			wc.hInstance = hInstance;
			wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
			wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
			wc.lpszClassName = TEXT("GameWindowClass");

			RegisterClassEx(&wc);


			hWindow = CreateWindowEx(0,
				TEXT("GameWindowClass"),    // name of the window class
				TEXT("Demo"),   // title of the window
				WS_OVERLAPPEDWINDOW,    // window style
				100,    // x-position of the window
				100,    // y-position of the window
				1024,    // width of the window
				768,    // height of the window
				nullptr,    // we have no parent window, NULL
				nullptr,    // we aren't using menus, NULL
				hInstance,    // application handle
				nullptr);    // used with multiple windows, NULL

			ShowWindow(hWindow, SW_SHOWNORMAL);
		}
		void Win32Game::CreateAndSetOpenGLContext()
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

			hDeviceContext = GetWindowDC(hWindow);

			int pixelFormatIndex = ChoosePixelFormat(hDeviceContext, &pfd);
			SetPixelFormat(hDeviceContext, pixelFormatIndex, &pfd);

			hGlContext = wglCreateContext(hDeviceContext);
			wglMakeCurrent(hDeviceContext, hGlContext);
		}

		LRESULT CALLBACK Win32Game::WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
		{
			switch (message)
			{
			case WM_DESTROY:
				PostQuitMessage(0);
				return 0;
			default:
				return DefWindowProc(hWnd, message, wParam, lParam);
			}
		}
		DWORD WINAPI Win32Game::ThreadProc(LPVOID lpParameter)
		{
			Win32Game* game = static_cast<Win32Game*>(lpParameter);

			photon::job::JobService::ThreadWork();

			return 0;
		}
	}
}

#endif