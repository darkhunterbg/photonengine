#define WIN32_LEAN_AND_MEAN


#include <Windows.h>

#include <Photon/Services/MemoryService.h>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	void* t0 = photon::services::MemAllocatePage(Kilobytes(1), false);
	void* t1 = photon::services::MemAllocatePage(Megabytes(1), false);
	void* t2 = photon::services::MemAllocatePage(Gigabytes(1), false);

	photon::services::MemFreeNonPersistent();

	bool result;
	result = photon::services::MemFreePage(t0);
	result = photon::services::MemFreePage(t1);
	result = photon::services::MemFreePage(t2);

	return 0;
}