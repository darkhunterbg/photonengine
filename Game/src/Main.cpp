#include <Windows.h>

#include <photon\PE.h>

#include <photon\Platform.h>
#include <photon\Platform\Win32Platform.h>
#include <photon\Services\MemoryService.h>

constexpr int GetValue()
{
	return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	photon::Platform::Initialize();
	photon::MemoryService::Initialize();

	photon::MemoryService::Uninitialize();
	photon::Platform::Uninitialize();

	return 0;
}