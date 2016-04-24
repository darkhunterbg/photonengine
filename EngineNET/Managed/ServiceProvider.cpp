#include "ServiceProvider.h"
#include <Photon/Services.h>

namespace Photon
{
	void ServiceProvider::InitializeServices()
	{
		photon::services::InitializeServices();
		Photon::Memory::MemoryService::Instance = gcnew Photon::Memory::MemoryService(photon::services::glMemoryService);
	}

	void ServiceProvider::UninitializeServices()
	{
		photon::services::UninitializeServices();
	}

	Photon::Memory::MemoryService^ ServiceProvider::MemoryService::get()
	{
		return Photon::Memory::MemoryService::Instance;
	}

}