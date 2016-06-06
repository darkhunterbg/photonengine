

#include <photon\Platform\Win32Game.h>
#include <Windows.h>

#include <photon\Macro.h>
#include <photon\Services\SceneService.h>
#include <photon\Services\AssetsService.h>

#include <photon\Text.h>
#include <photon\Types.h>

#include "TestScene.cpp"

#include <locale.h>

constexpr int GetValue()
{
	return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	setlocale(LC_ALL, "");


	static const int BUFFER_SIZE = _MAX_PATH * 4;
	TCHAR buffer[_MAX_PATH * 4];
	GetFullPathName(TEXT("..\\Assets\\"), BUFFER_SIZE, buffer, nullptr);

	TestScene scene;

	photon::Win32Game::Initialize(hInstance, buffer);

	photon::gl_SceneService->PushScene(&scene);

	photon::Win32Game::Run();
	photon::Win32Game::Uninitialize();


	return 0;
}