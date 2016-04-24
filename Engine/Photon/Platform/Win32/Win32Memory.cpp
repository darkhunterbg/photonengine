
#include "../../PE.h"

#if (PLATFORM == WINDOWS)

#include "../Memory.h"
#include "Win32Platform.h"

void* photon::platform::AllocateMemory( size_t size, void* baseAddress)
{
	return VirtualAlloc(baseAddress, size, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
}

bool photon::platform::DeallocateMemory(void* address, size_t size)
{
	return VirtualFree(address, size, MEM_RELEASE) == 0;
}


#endif
