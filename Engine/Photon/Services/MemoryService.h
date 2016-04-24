#pragma once

#include "../PE.h"
#include <stddef.h>

namespace photon
{
	namespace services
	{
		ALIGN(8)
			struct MemoryPage
		{
			MemoryPage* next;
			MemoryPage* prev;
			size_t size;
			bool persistent;
			void* memoryPtr;
		};

		EXPORT void* MemAllocatePage(size_t size, bool persistent = true);
		EXPORT bool MemFreePage(void* pagePtr);
		EXPORT void MemFreeNonPersistent();
	};

}