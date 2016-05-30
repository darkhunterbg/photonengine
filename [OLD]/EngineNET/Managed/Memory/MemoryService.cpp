#include "MemoryService.h"
#include <Photon/Memory/MemoryService.h>

namespace Photon
{
	namespace Memory
	{
		MemoryService::MemoryService(photon::memory::MemoryService* native) :
			native(native)
		{

		}
		MemoryService::~MemoryService()
		{

		}

		MemoryService^ MemoryService::Instance::get()
		{
			return instance;
		}
		void MemoryService::Instance::set(MemoryService^ value)
		{
			instance = value;
		}


		System::IntPtr MemoryService::Allocate(System::UInt32 size, bool persistent)
		{
			return System::IntPtr(native->AllocatePage((size_t)size, persistent));
		}

		System::UInt32 MemoryService::Free(System::IntPtr pageHandle)
		{
			return System::UInt32(native->FreePage(pageHandle.ToPointer()));
		}

		System::UInt32 MemoryService::FreeNonPersistent()
		{
			return System::UInt32(native->FreeNonPersistent());
		}
	}
}