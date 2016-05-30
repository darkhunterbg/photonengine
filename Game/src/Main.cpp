
#include <photon\PE.h>

#include <photon\Platform\Win32Game.h>

#include <Windows.h>


class Game : public photon::Win32Game
{
public:
	Game(void* instance) : Win32Game(instance) {}
	~Game() {}
	
};

constexpr int GetValue()
{
	return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	Game* game = new Game((void*)hInstance);
	game->Run();
	delete game;

	return 0;
}