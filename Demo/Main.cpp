#define WIN32_LEAN_AND_MEAN


#include <Windows.h>

#include <Photon/Services/Services.h>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	photon::services::InitializeServices();


	void* t0 = photon::services::glMemoryService->AllocatePage(Kilobytes(1), false);
	void* t1 = photon::services::glMemoryService->AllocatePage(Megabytes(1), false);
	void* t2 = photon::services::glMemoryService->AllocatePage(Gigabytes(1), false);

	photon::services::glMemoryService->FreePage(t0);
	photon::services::glMemoryService->FreePage(t1);
	photon::services::glMemoryService->FreePage(t2);

	photon::services::UninitializeServices();

	return 0;
}