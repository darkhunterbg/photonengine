#pragma once

#include "../Macro.h"
#include "../Types.h"
#include "MemoryStack.h"
namespace photon
{
	static const int FILE_PATH_CHAR_SIZE = 256 * 4;

	class EXPORT AssetsService
	{
		DISABLE_COPY(AssetsService);

	private:
		MemoryStack* scratchMemory;
		TCHAR root[FILE_PATH_CHAR_SIZE];

		AssetsService(size_t scratchMemorySize);
		~AssetsService();

	public:
		static AssetsService* Initialize(size_t scratchMemorySize, MemoryStack& stack);
		static void Uninitialize();

		void SetRoot(const TCHAR* root);
	};

	EXPORT extern AssetsService* gl_AssetsService;
}