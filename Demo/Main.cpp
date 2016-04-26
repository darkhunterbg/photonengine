#define WIN32_LEAN_AND_MEAN


#include <Photon/Platform/Win32/Win32Platform.h>

#include <Photon/Graphics/GraphicsService.h>
#include <Photon/Memory/MemoryService.h>
#include <Photon/Memory/MemoryStack.h>
#include <Photon/Platform/Win32/Win32OpenGL.h>

HWND CreateAndShowWindow(HINSTANCE hInstance);


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	auto handler = CreateAndShowWindow(hInstance);

	//================== INIT ============================
	photon::memory::MemoryService::Initialize();

	void* memory = photon::glMemoryService->AllocatePage(Megabytes(1));
	auto memstack = photon::memory::MemoryStack::New(memory, Megabytes(1));

	photon::platform::OpenGLContext context = photon::platform::CreateOpenGLContext(handler);
	bool s = photon::platform::SetCurrentOpenGLWindow(handler, context);

	photon::graphics::GraphicsService::Initialize(*memstack);
	//======================================================

	MSG msg;

	while (true)
	{
		while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}


		if (msg.message == WM_QUIT)
			break;

		//================ GAME LOOP ============================
		photon::platform::SwapOpenGLBuffers(context);
		//======================================================

	}

	//================ UNINIT ===============================
	photon::graphics::GraphicsService::Uninitialize();

	photon::platform::SetCurrentOpenGLWindow(nullptr, context);
	photon::platform::DeleteOpenGLContext(context);


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