#include "MemoryService.h"
#include <Photon/Services/MemoryService.h>

namespace Photon
{
	namespace Services
	{
		System::IntPtr MemoryService::Allocate(System::UInt32 size, bool persistent)
		{
			return System::IntPtr(photon::services::MemAllocatePage((size_t)size, persistent));
		}

		bool MemoryService::Free(System::IntPtr pageHandle)
		{
			return photon::services::MemFreePage(pageHandle.ToPointer());
		}

		void MemoryService::FreeNonPersistent()
		{
			photon::services::MemFreeNonPersistent();
		}
	}
}