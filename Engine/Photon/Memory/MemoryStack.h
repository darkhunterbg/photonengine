#pragma once

#include "../PE.h"
#include <stddef.h>

namespace photon
{
	namespace memory
	{
		class EXPORT MemoryStack
		{
		private:
			DISABLE_COPY(MemoryStack);
			DISABLE_NEW_DELETE(MemoryStack);

			void* memoryPtr;
			size_t memorySize;
			size_t allocated;
		
			MemoryStack(void* memory, size_t memorySize);
			~MemoryStack() = delete;
		public:
			static MemoryStack* New(void* memory, size_t memorySize);
			static void Delete(MemoryStack* stack);

			void* Allocate(size_t size);
			void Clear();
		};
	}
}