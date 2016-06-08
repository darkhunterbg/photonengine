#include "AssetsService.h"
#include "MemoryService.h"
#include "../Text.h"
#include "../Alloc.h"

namespace photon
{
	AssetsService* gl_AssetsService = nullptr;

	AssetsService::AssetsService(size_t scratchMemorySize)
	{
		void* ptr = gl_MemoryService->AllocatePage(scratchMemorySize);
		scratchMemory = MemoryStack::New(ptr, scratchMemorySize);
	}
	AssetsService::~AssetsService()
	{
		int assetsCount = assets.GetCount();
		for (int i = 0; i < assetsCount; ++i)
		{
			gl_MemoryService->FreePage(assets[i].memory);
		}

		MemoryStack::Delete(scratchMemory);
	}

	AssetsService* AssetsService::Initialize(size_t scratchMemorySize, MemoryStack& stack)
	{
		ASSERT(gl_AssetsService == nullptr);
		ASSERT(scratchMemorySize > 0);

		gl_AssetsService = MEM_NEW(stack, AssetsService)(scratchMemorySize);

		return gl_AssetsService;
	}
	void AssetsService::Uninitialize()
	{
		ASSERT(gl_AssetsService);

		gl_AssetsService->~AssetsService();
		gl_AssetsService = nullptr;
	}

	void AssetsService::SetRoot(const TCHAR* path)
	{
		text::Copy(path, root);
	}
	AssetsHandler AssetsService::GetExistingAsset(const char* assetPath)
	{
		ASSERT(text::Length(assetPath) < ASSET_PATH_SIZE);

		int assetsCount = assets.GetCount(); 
		for (int i = 0; i < assetsCount; ++i)
		{
			if (text::Compare(assets[i].path, assetPath) == 0)
				return (AssetsHandler)i;
		}

		return (AssetsHandler)-1;
	}
	TextAsset AssetsService::GetTextAsset(const char* assetPath)
	{
		AssetsHandler handler = GetExistingAsset(assetPath);

		if (handler < 0)
		{
			handler = assets.GetCount();
			AssetEntry& asset = assets.New();
		
			text::Copy(assetPath, asset.path);

#pragma message("Fix this code for cross-platforming")
			TCHAR fullPath[FILE_PATH_CHAR_SIZE];
			text::Copy(root, fullPath);
			text::Append(fullPath, assetPath);

			FileHandler file = Platform::FileOpen(fullPath);
			size_t fileSize = Platform::GetFileSize(file);
#pragma message("Need better allocation")
			void* ptr = gl_MemoryService->AllocatePage(fileSize);
			Platform::ReadFromFile(file, ptr, fileSize);
			asset.memory = ptr;
			asset.memorySize = fileSize;
			Platform::FileClose(file);
		}

		TextAsset asset;
		asset.handler = handler;
		asset.text = (char*)assets[handler].memory;
		asset.textLength = assets[handler].memorySize;
		return asset;

	}
}