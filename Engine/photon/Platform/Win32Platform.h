#pragma once

#include "../PE.h"

#if defined(WINDOWS)
namespace photon
{
	class EXPORT Win32Platfrom
	{
	private:
		static bool initialized;

		Win32Platfrom() = delete;
		~Win32Platfrom() = delete;
	public:
		static void* MemoryAlloc(size_t size);
		static bool MemoryFree(void* address, size_t size);

		static void Initialize();
		static void Uninitialize();

	} typedef Platform;
}
#endif