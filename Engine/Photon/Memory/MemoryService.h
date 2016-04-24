#pragma once

#include "../PE.h"
#include <stddef.h>

namespace photon
{
	namespace memory
	{
		ALIGN(8) struct MemoryPage
		{
			MemoryPage* next;
			MemoryPage* prev;
			size_t size;
			bool persistent;
			void* memoryPtr;
		};

		class EXPORT MemoryService
		{
		private:
			MemoryPage* firstPage;
			MemoryPage* lastPage;

			MemoryService();
			~MemoryService();
		public:
			static MemoryService* Initialize();
			static void Uninitialize();

			void* AllocatePage(size_t size, bool persistent = true);
			size_t FreePage(void* pagePtr);
			size_t FreeNonPersistent();
		};


		EXPORT extern MemoryService* glMemoryService;

	}
}