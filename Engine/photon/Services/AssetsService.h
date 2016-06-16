#pragma once

#include "../Macro.h"
#include "../Types.h"
#include "MemoryStack.h"
#include "Assets.h"
#include "../Utils/Array.h"
#include "../Text.h"

namespace photon
{
	static const int FILE_PATH_CHAR_SIZE = 256 * 4;
	static const int ASSET_PATH_SIZE = 128;

	template<class ASSET>
	struct EXPORT AssetEntry
	{
		char path[ASSET_PATH_SIZE];
		ASSET asset;
		void* memory ;
		size_t memorySize ;
	};

	class EXPORT AssetsService
	{
		DISABLE_COPY(AssetsService);

	private:
		static const int MAX_ASSET_TYPE = 128;

		MemoryStack* scratchMemory;
		TCHAR root[FILE_PATH_CHAR_SIZE];

		Array<AssetEntry<TextureAsset>, MAX_ASSET_TYPE> textures;
		Array<AssetEntry<TextAsset>, MAX_ASSET_TYPE> texts;
		Array<AssetEntry<ShaderAsset>, MAX_ASSET_TYPE> shaders;

		AssetsService(size_t scratchMemorySize);
		~AssetsService();

		template<class ASSET, unsigned int SIZE>
		ASSET* GetExistingAsset(const char* assetPath,   Array<AssetEntry<ASSET>, SIZE>& assets)
		{
			ASSERT(text::Length(assetPath) < ASSET_PATH_SIZE);

			int assetsCount = assets.Count();
			for (int i = 0; i < assetsCount; ++i)
			{
				if (text::Compare(assets.Get(i).path, assetPath) == 0)
					return &assets.Get(i).asset;
			}

			return nullptr;
		}

		template<class ASSET, unsigned int SIZE>
		AssetsHandler NewAsset(const char* assetPath, Array<AssetEntry<ASSET>, SIZE>& assets)
		{
			AssetsHandler handler = assets.Count();

			AssetEntry<ASSET>& entry = assets.New();

			text::Copy(assetPath, entry.path);

#pragma message("Fix this code for cross-platforming")
			TCHAR fullPath[FILE_PATH_CHAR_SIZE];
			text::Copy(root, fullPath);
			text::Append(fullPath, assetPath);

			FileHandler file = Platform::FileOpen(fullPath);
			size_t fileSize = Platform::GetFileSize(file);
#pragma message("Need better allocation")
			void* ptr = gl_MemoryService->AllocatePage(fileSize);
			Platform::ReadFromFile(file, ptr, fileSize);
			entry.memory = ptr;
			entry.memorySize = fileSize;
			Platform::FileClose(file);
			entry.asset = {};

			return handler;
		}
	public:
		static AssetsService* Initialize(size_t scratchMemorySize, MemoryStack& stack);
		static void Uninitialize();

		TextAsset& GetTextAsset(const char* assetPath);
		TextureAsset& GetTextureAsset(const char* assetPath);
		ShaderAsset& GetShaderAsset(const char* assetPath);


		void SetRoot(const TCHAR* root);
	};

	EXPORT extern AssetsService* gl_AssetsService;
}