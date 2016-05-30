#include "MemoryStack.h"

namespace photon
{
	MemoryStack::MemoryStack(void* mem, size_t memSize) :
		memoryPtr(mem), memorySize(memSize), allocated(0)
	{}

	MemoryStack* MemoryStack::New(void* mem, size_t memSize)
	{
		ASSERT(memSize > sizeof(MemoryStack));

		void* freeMem = (void*)((size_t)mem + sizeof(MemoryStack));

		return new(mem) MemoryStack(freeMem, memSize - sizeof(MemoryStack));
	}


	void* MemoryStack::Allocate(size_t size)
	{
		ASSERT(size < memorySize - allocated);

		//Align by ptr size

		static const size_t ptrSize = sizeof(void*);
		size_t remain = size % ptrSize;
		if(remain)
			size = (size / ptrSize) + ptrSize;

		void* result = (void*)((size_t)memoryPtr + allocated);
		allocated += size;

		return result;
	}

	void MemoryStack::Clear()
	{
		allocated = 0;
	}
}