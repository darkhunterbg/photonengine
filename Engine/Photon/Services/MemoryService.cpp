#include "MemoryService.h"
#include "../Platform/Memory.h"

namespace photon
{
	namespace services
	{
		MemoryPage* memFirstPage = nullptr;
		MemoryPage* memLastPage = nullptr;

		void* MemAllocatePage(size_t size, bool persistent)
		{
			if (size == 0)
				return nullptr;

			size += sizeof(MemoryPage);

			//TODO: Apply aligment  based on platform page size
			//Check  https://msdn.microsoft.com/en-us/library/windows/desktop/ms724958(v=vs.85).aspx

			MemoryPage* page = (MemoryPage*)platform::AllocateMemory(size);

			if (page == nullptr)
				return nullptr;

			page->memoryPtr = page + sizeof(MemoryPage);
			page->next = nullptr;
			page->size = size;
			page->persistent = persistent;

			if (!memFirstPage)
				memFirstPage = page;

			page->prev = memLastPage;

			if (memLastPage)
				memLastPage->next = page;

			memLastPage = page;

			return page->memoryPtr;
		}

		bool MemFreePage(void* pagePtr)
		{
			MemoryPage* page = memFirstPage;
			while (page)
			{
				if (page->memoryPtr == pagePtr)
				{
					if (page == memFirstPage)
						memFirstPage = page->next;

					if (page == memLastPage)
						memLastPage = page->prev;

					if (page->prev)
						page->prev->next = page->next;

					if (page->next)
						page->next->prev = page->prev;

					return platform::DeallocateMemory(page, page->size);
				}

				page = page->next;
			}
			return false;
		}

		void MemFreeNonPersistent()
		{
			//TODO: better dealloc (without calling MemFreePage)
			MemoryPage* page = memFirstPage;
			while (page)
			{
				if (!page->persistent)
				{
					void* memPtr = page->memoryPtr;
					page = page->next;
					MemFreePage(memPtr);
				}
				else
				{
					page = page->next;
				}
			}
		}
	}
}