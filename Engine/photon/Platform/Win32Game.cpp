#pragma once

#include "../Macro.h"
#include "../Platform/Platform.h"

#if PLATFORM == WINDOWS

#include "Win32Game.h"

#include "../Services/GraphicsService.h"
#include "../Services/MemoryService.h"
#include "../Services/SceneService.h"
#include "../Services/AssetsService.h"

#include "../Platform/Win32Platform.h"

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

namespace photon
{
	void* hInstance;
	void* hWindow;
	MemoryStack* memStack;
	GraphicsAPI* api;


	LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

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
				gl_SceneService->Update();
				gl_GraphicsService->PresentFrame();
				//======================================================
				
				deltaTime -= ((freq.QuadPart * 16'666) / (1000 * 1000));
			}

		}
	}

	void Win32Game::Initialize(void* instance)
	{
		hInstance = instance;

		CreateAndShowWindow();

		photon::Win32Platfrom::Initialize();

		photon::MemoryService::Initialize();
		void* memory = photon::gl_MemoryService->AllocatePage(Megabytes(1));
		memStack = photon::MemoryStack::New(memory, Megabytes(1));

		GraphicsAPIParam param = {};
#if GRAPHICS_API == DIRECTX
		param.hWindow = hWindow;
#endif
#if GRAPHICS_API == OPENGL
		param.createParam.hwindow = hWindow;
#endif
		api = photon::GraphicsAPI::InitializeAPI(*memStack, param);
		photon::GraphicsService::Initialize(api, *memStack);
		photon::AssetsService::Initialize(Megabytes(4), *memStack);
		photon::SceneService::Initialize(*memStack);
	}
	void Win32Game::Uninitialize()
	{
#if DEBUG >= DEBUG_FULL
		photon::SceneService::Uninitialize();
		photon::AssetsService::Uninitialize();
		photon::GraphicsService::Uninitialize();
		photon::GraphicsAPI::UninitializeAPI(api);

		photon::MemoryStack::Delete(memStack);
		photon::MemoryService::Uninitialize();
		photon::Win32Platfrom::Uninitialize();

		DestroyWindow((HWND)hWindow);
#endif
	}
	void Win32Game::CreateAndShowWindow()
	{
		WNDCLASSEX wc;

		ZeroMemory(&wc, sizeof(WNDCLASSEX));

		wc.cbSize = sizeof(WNDCLASSEX);
		wc.style = CS_HREDRAW | CS_VREDRAW;
		wc.lpfnWndProc = WindowProc;
		wc.hInstance = (HINSTANCE)hInstance;
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
			(HINSTANCE)hInstance,    // application handle
			nullptr);    // used with multiple windows, NULL

		ShowWindow((HWND)hWindow, SW_SHOWNORMAL);
		SetFocus((HWND)hWindow);
	}

	LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
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
}

#endif