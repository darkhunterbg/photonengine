#pragma once

#include "../Macro.h"
#include "../Types.h"
#include "MemoryStack.h"
#include "Assets.h"
#include "../Utils/Array.h"

namespace photon
{
	static const int FILE_PATH_CHAR_SIZE = 256 * 4;
	static const int ASSET_PATH_SIZE = 128;

	struct AssetEntry
	{
		void* memory;
		size_t memorySize;
		char path[ASSET_PATH_SIZE];
	};

	class EXPORT AssetsService
	{
		DISABLE_COPY(AssetsService);

	private:
		static const int MAX_ASSETS = 1024;

		MemoryStack* scratchMemory;
		TCHAR root[FILE_PATH_CHAR_SIZE];

		Array<AssetEntry, MAX_ASSETS> assets;

		AssetsService(size_t scratchMemorySize);
		~AssetsService();

		AssetsHandler GetExistingAsset(const char* assetPath);
	public:
		static AssetsService* Initialize(size_t scratchMemorySize, MemoryStack& stack);
		static void Uninitialize();

		TextAsset GetTextAsset(const char* assetPath);

		void SetRoot(const TCHAR* root);
	};

	EXPORT extern AssetsService* gl_AssetsService;
}