#define WIN32_LEAN_AND_MEAN


#include <Photon/Platform/Win32/Win32Platform.h>

#include <Photon/Graphics/GraphicsService.h>
#include <Photon/Memory/MemoryService.h>
#include <Photon/Memory/MemoryStack.h>
#include <Photon/Platform/Win32/Win32OpenGL.h>


LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, message, wParam, lParam);
}



int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{

	hInstance = GetModuleHandle(nullptr);

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
		L"ASDF",   // title of the window
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


	photon::memory::MemoryService::Initialize();

	void* memory = photon::glMemoryService->AllocatePage(Megabytes(1));
	auto memstack = photon::memory::MemoryStack::New(memory, Megabytes(1));

	photon::platform::OpenGLContext context = photon::platform::CreateOpenGLContext(handler);

	photon::graphics::GraphicsService::Initialize(&context, *memstack);


	photon::graphics::GraphicsService::Uninitialize();

	DeleteOpenGLContext(context);
	memstack->Clear();
	photon::memory::MemoryService::Uninitialize();


	return 0;
}