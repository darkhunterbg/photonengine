#include "Services.h"


void photon::services::InitializeServices()
{
	if (glMemoryService)
		return;

	glMemoryService = MemoryService::Initialize();
}

void photon::services::UninitializeServices()
{
	MemoryService::Uninitialize(glMemoryService);
}