#include "ServiceProvider.h"
#include <Photon/Services/Services.h>

namespace Photon
{
	namespace Services
	{
		void ServiceProvider::InitializeServices()
		{
			photon::services::InitializeServices();
			Photon::Services::MemoryService::Instance = gcnew Photon::Services::MemoryService(photon::services::glMemoryService);
		}

		void ServiceProvider::UninitializeServices()
		{
			photon::services::UninitializeServices();
		}

		Photon::Services::MemoryService^ ServiceProvider::MemoryService::get()
		{
			return Photon::Services::MemoryService::Instance;
		}

	}
}