#include "MemoryService.h"

#include "../Platform/Platform.h"

namespace photon
{
	MemoryService* gl_MemoryService = nullptr;

	MemoryService::MemoryService() :
		firstPage(nullptr), lastPage(nullptr)
	{

	}
	MemoryService::~MemoryService()
	{

	}

	MemoryService* MemoryService::Initialize()
	{
		ASSERT(gl_MemoryService == nullptr);

		gl_MemoryService = new MemoryService();
		return gl_MemoryService;
	}
	void MemoryService::Uninitialize()
	{
		ASSERT(gl_MemoryService);

		delete gl_MemoryService;
		gl_MemoryService = nullptr;
	}

	void* MemoryService::AllocatePage(size_t size, bool persistent)
	{
		ASSERT(size);

		size += sizeof(MemoryPage);

		//TODO: Apply aligment  based on platform page size
		//Check  https://msdn.microsoft.com/en-us/library/windows/desktop/ms724958(v=vs.85).aspx

		MemoryPage* page = (MemoryPage*)Platform::MemoryAlloc(size);

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

				bool success = Platform::MemoryFree(page, page->size);
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