#include "MemoryService.h"
#include "../Platform/Memory.h"

namespace photon
{
	namespace services
	{
		MemoryService* glMemoryService = nullptr;

		MemoryService::MemoryService() :
			firstPage(nullptr), lastPage(nullptr)
		{

		}
		MemoryService::~MemoryService()
		{

		}

		MemoryService* MemoryService::Initialize()
		{
			MemoryService* service = new MemoryService();
			return service;
		}
		void MemoryService::Uninitialize(MemoryService* service)
		{
			delete service;
		}

		void* MemoryService::AllocatePage(size_t size, bool persistent)
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

			if (!firstPage)
				firstPage = page;

			page->prev = lastPage;

			if (lastPage)
				lastPage->next = page;

			lastPage = page;

			return page->memoryPtr;
		}

		size_t MemoryService::FreePage(void* pagePtr)
		{

			MemoryPage* page = firstPage;
			while (page)
			{
				if (page->memoryPtr == pagePtr)
				{
					if (page == firstPage)
						firstPage = page->next;

					if (page == lastPage)
						lastPage = page->prev;

					if (page->prev)
						page->prev->next = page->next;

					if (page->next)
						page->next->prev = page->prev;

					size_t freed = page->size;

					bool success = platform::DeallocateMemory(page, page->size);
					return success ? freed : 0;
				}

				page = page->next;
			}
			return 0;
		}

		size_t MemoryService::FreeNonPersistent()
		{
			size_t freed = 0;

			//TODO: better dealloc (without calling MemFreePage)
			MemoryPage* page = firstPage;
			while (page)
			{
				if (!page->persistent)
				{
					void* memPtr = page->memoryPtr;
					page = page->next;
					freed += FreePage(memPtr);
				}
				else
				{
					page = page->next;
				}
			}

			return freed;
		}
	}
}