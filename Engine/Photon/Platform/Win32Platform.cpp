#include "../PE.h"

#if (PLATFORM == WINDOWS)

#define WIN32_LEAN_AND_MEAN

#include <Windows.h>

#include "Win32Platform.h"

namespace photon
{
	namespace platform
	{
		void* Win32Platfrom::MemoryAlloc(size_t size)
		{
			return VirtualAlloc(nullptr, size, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
		}

		bool Win32Platfrom::MemoryFree(void* address, size_t size)
		{
			return VirtualFree(address, size, MEM_RELEASE) == 0;
		}
	}

	platform::Win32Platfrom* gl_Platform = nullptr;
}


#endif