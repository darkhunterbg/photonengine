

#include <photon\Platform\Win32Game.h>
#include <Windows.h>

#include <photon\Macro.h>

constexpr int GetValue()
{
	return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	photon::Win32Game::Initialize(hInstance);
	photon::Win32Game::Run();
	photon::Win32Game::Uninitialize();


	return 0;
}