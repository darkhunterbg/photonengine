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
		int assetsCount = texts.Count();
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

			LoadTextureType type;

			if (text::EndsWith(assetPath, "dds"))
				type = LoadTextureType::DDS;
			if (text::EndsWith(assetPath, "bmp"))
				type = LoadTextureType::Bitmap;

			asset->textureID = gl_GraphicsService->LoadTexture(textures[handler].memory, type);
			gl_MemoryService->FreePage(textures[handler].memory);
			textures[handler].memory = nullptr;
			textures[handler].memorySize = 0;
		}
		return *asset;
	}
	ShaderAsset& AssetsService::GetShaderAsset(const char* assetPath)
	{
		ShaderAsset* asset = GetExistingAsset(assetPath, shaders);

		if (!asset)
		{
			AssetsHandler handler = NewAsset(assetPath, shaders);
			asset = &shaders[handler].asset;
			asset->handler = handler;

			char* text = (char*)shaders[handler].memory;

			if (text::EndsWith(assetPath, ".v"))
				asset->type = ShaderType::VERTEX_SHADER;
			if (text::EndsWith(assetPath, ".g"))
				asset->type = ShaderType::GEOMETRY_SHADER;
			if (text::EndsWith(assetPath, ".f"))
				asset->type = ShaderType::FRAGMENT_SHADER;

			asset->shaderID = gl_GraphicsService->LoadShader(asset->type, text);

		}

		return *asset;
	}

}