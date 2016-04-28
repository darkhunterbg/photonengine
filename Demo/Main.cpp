#define WIN32_LEAN_AND_MEAN

#include <Windows.h>


#include <Photon/Graphics/GraphicsService.h>
#include <Photon/Memory/MemoryService.h>
#include <Photon/Memory/MemoryStack.h>
#include <Photon/Platform/Win32Platform.h>


#include <gl\GL.h>


HWND CreateAndShowWindow(HINSTANCE hInstance);

HGLRC CreateOpenGLContext(HWND window);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	auto handler = CreateAndShowWindow(hInstance);

	//================== INIT ============================
	photon::memory::MemoryService::Initialize();

	void* memory = photon::gl_MemoryService->AllocatePage(Megabytes(1));
	auto memstack = photon::memory::MemoryStack::New(memory, Megabytes(1));

	HGLRC context = CreateOpenGLContext(handler);
	HDC dc = GetWindowDC(handler);
	wglMakeCurrent(dc, context);

	photon::graphics::GraphicsService::Initialize(*memstack);
	//======================================================

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

		LONGLONG  deltaMS = (1000 * time.QuadPart / freq.QuadPart);
		if (deltaMS >= 16)
		{
			//================ GAME LOOP ============================
			SwapBuffers(dc);
			//======================================================
			glClear(GL_COLOR_BUFFER_BIT);
			deltaTime = { 0 };
		}

	}

	//================ UNINIT ===============================
	photon::graphics::GraphicsService::Uninitialize();

	wglMakeCurrent(nullptr, context);
	wglDeleteContext(context);

	memstack->Clear();
	photon::memory::MemoryService::Uninitialize();
	//======================================================


	return 0;
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


HGLRC CreateOpenGLContext(HWND window)
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

	return wglCreateContext(windowDC);
}

HWND CreateAndShowWindow(HINSTANCE hInstance)
{
	WNDCLASSEX wc;

	ZeroMemory(&wc, sizeof(WNDCLASSEX));

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WindowProc;
	wc.hInstance = hInstance;
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.lpszClassName = TEXT("WindowClass1");

	RegisterClassEx(&wc);


	HWND handler = CreateWindowEx(0,
		TEXT("WindowClass1"),    // name of the window class
		L"Demo",   // title of the window
		WS_OVERLAPPEDWINDOW,    // window style
		100,    // x-position of the window
		100,    // y-position of the window
		1024,    // width of the window
		768,    // height of the window
		nullptr,    // we have no parent window, NULL
		nullptr,    // we aren't using menus, NULL
		hInstance,    // application handle
		nullptr);    // used with multiple windows, NULL

	ShowWindow(handler, SW_SHOWNORMAL);

	return handler;
}