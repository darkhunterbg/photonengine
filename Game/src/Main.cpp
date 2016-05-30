#include <Windows.h>

constexpr int GetValue()
{
	return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	int x = GetValue();

	++x;

	return 0;
}