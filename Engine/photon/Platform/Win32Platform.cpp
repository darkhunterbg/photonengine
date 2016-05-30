#include "../PE.h"

#if defined(WINDOWS)

#define WIN32_LEAN_AND_MEAN

#include <Windows.h>

#include "Win32Platform.h"

namespace photon
{
	bool Win32Platfrom::initialized = false;

	void Win32Platfrom::Initialize()
	{
		ASSERT(!initialized);

		initialized = true;
	}
	void Win32Platfrom::Uninitialize()
	{
		ASSERT(initialized);
	}


	void* Win32Platfrom::MemoryAlloc(size_t size)
	{
		ASSERT(size > 0);

		return VirtualAlloc(nullptr, size, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
	}

	bool Win32Platfrom::MemoryFree(void* address, size_t size)
	{
		ASSERT(address);

		ASSERT(size > 0);

		return VirtualFree(address, size, MEM_RELEASE) == 0;
	}

}


#endif