#pragma once

#include "../Macro.h"
#include "MemoryStack.h"

namespace photon
{
	class EXPORT AssetsService
	{
		DISABLE_COPY(AssetsService);

	private:
		MemoryStack* scratchMemory;

		AssetsService(size_t scratchMemorySize);
		~AssetsService();

	public:
		static AssetsService* Initialize(size_t scratchMemorySize, MemoryStack& stack);
		static void Uninitialize();
	};

	EXPORT extern AssetsService* gl_AssetsService;
}