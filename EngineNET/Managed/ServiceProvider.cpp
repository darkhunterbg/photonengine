#include "ServiceProvider.h"
#include <Photon/Memory/MemoryService.h>

namespace Photon
{
	void ServiceProvider::InitializeServices()
	{
		auto nativeService = photon::memory::MemoryService::Initialize();
		Photon::Memory::MemoryService::Instance = gcnew Photon::Memory::MemoryService(nativeService);
	}

	void ServiceProvider::UninitializeServices()
	{
		photon::memory::MemoryService::Uninitialize();
		Photon::Memory::MemoryService::Instance = nullptr;
	}

	Photon::Memory::MemoryService^ ServiceProvider::MemoryService::get()
	{
		return Photon::Memory::MemoryService::Instance;
	}

}