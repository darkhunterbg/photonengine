#define WIN32_LEAN_AND_MEAN

#include <Windows.h>

#include <Photon\Platform\Win32Game.h>


class Game : public photon::platform::Win32Game
{
public : 
	Game(HINSTANCE hInstance) :Win32Game(hInstance)
	{

	}
	~Game()
	{

	}
};

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	Game* game = new Game(hInstance);

	game->Run();

	delete game;



	return 0;
}
