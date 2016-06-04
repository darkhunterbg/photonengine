

#include <photon\Platform\Win32Game.h>
#include <Windows.h>

#include <photon\Macro.h>

#include <photon\Services\SceneService.h>

#include "TestScene.cpp"

constexpr int GetValue()
{
	return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{

	TestScene scene;

	photon::Win32Game::Initialize(hInstance);

	photon::gl_SceneService->PushScene(&scene);

	photon::Win32Game::Run();
	photon::Win32Game::Uninitialize();


	return 0;
}