

#include <photon\Platform\Win32Game.h>
#include <Windows.h>

#include <photon\Macro.h>
#include <photon\Services\SceneService.h>
#include <photon\Services\AssetsService.h>

#include <photon\Text.h>
#include <photon\Types.h>

#include "TestScene.h"

#include <locale.h>

#include <photon\Math\Vector.h>
#include <photon\Math\Matrix.h>



int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	Matrix m = {};
	Matrix n = {};

	m[0][0] = 1;
	m[0][1] = 2;
	m[0][2] = 3;
	m[1][0] = 4;
	m[1][1] = 5;
	m[1][2] = 6;

	n[0][0] = 7;
	n[0][1] = 8;
	n[1][0] = 9;
	n[1][1] = 10;
	n[2][0] = 11;
	n[2][1] = 12;

	Matrix l = m*n;

	setlocale(LC_ALL, "");

	static const int BUFFER_SIZE = _MAX_PATH * 4;
	TCHAR buffer[_MAX_PATH * 4];
	GetFullPathName(TEXT("..\\..\\Assets\\"), BUFFER_SIZE, buffer, nullptr);

	TestScene scene;

	photon::Win32Game::Initialize(hInstance, buffer);

	photon::gl_SceneService->PushScene(&scene);

	photon::Win32Game::Run();
	photon::Win32Game::Uninitialize();


	return 0;
}