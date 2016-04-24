#pragma once

#include "../PE.h"
#include <stddef.h>


namespace photon
{
	namespace platform
	{
		void* AllocateMemory( size_t size, void* baseAddress = nullptr);
		bool DeallocateMemory(void* address, size_t size);
	}
}