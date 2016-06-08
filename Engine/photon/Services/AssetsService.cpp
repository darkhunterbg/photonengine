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
		int assetsCount = texts.GetCount();
		for (int i = 0; i < assetsCount; ++i)
			gl_MemoryService->FreePage(texts[i].memory);

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

	TextAsset& AssetsService::GetTextAsset(const char* assetPath)
	{
		TextAsset* asset = GetExistingAsset(assetPath, texts);

		if (!asset)
		{
			AssetsHandler handler = NewAsset(assetPath, texts);
			asset = &texts[handler].asset;
			asset->handler = handler;
			asset->text = (char*)texts[handler].memory;
			asset->textLength = (size_t)texts[handler].memorySize;
		}
	
		return *asset;

	}
	TextureAsset& AssetsService::GetTextureAsset(const char* assetPath)
	{
		TextureAsset* asset = GetExistingAsset(assetPath, textures);

		if (!asset)
		{
			AssetsHandler handler = NewAsset(assetPath, textures);
			asset = &textures[handler].asset;
			asset->handler = handler;

			char* filecode =(char*)textures[handler].memory;
			ASSERT(text::Compare(filecode, "DDS "));

			DDSHeader& header = *(DDSHeader*)((BYTE*)textures[handler].memory + 4);

			uint32_t blockSize = (header.fourCC == FourCCType::FOURCC_DXT1) ? 8 : 16;
			int numblocks = ((header.width + 3) / 4) * ((header.height + 3) / 4);

			uint32_t bufsize;
			if (header.linearSize != 0)
				bufsize = header.mipMapCount > 1 ? header.linearSize * 2 : header.linearSize;
			else
				bufsize = blockSize * numblocks;

			if (header.mipMapCount < 1)
				header.mipMapCount = 1;

			BYTE* buffer = (BYTE*)textures[handler].memory + sizeof(DDSHeader);

			TextureFormat format;

			switch (header.fourCC)
			{
			case FourCCType::FOURCC_DXT1: format = TextureFormat::DXT1; break;
			case FourCCType::FOURCC_DXT3: format = TextureFormat::DXT3; break;
			case FourCCType::FOURCC_DXT5: format = TextureFormat::DXT5; break;
			default:
				ASSERT(false);
			}

			asset->texture = gl_GraphicsService->CreateTexture(buffer, format, header.width, header.height, blockSize, header.mipMapCount);
		}
		return *asset;
	}
}