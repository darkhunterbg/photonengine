#pragma once

#include "../Macro.h"
#include "GraphicsService.h"

namespace photon
{
	typedef int AssetsHandler;

	struct EXPORT TextAsset
	{
		char* text;
		size_t textLength;
		AssetsHandler handler;
	};

	struct EXPORT TextureAsset
	{
		AssetsHandler handler;
		TextureHandler texture;
	};


	enum class FourCCType : uint32_t
	{
		FOURCC_DXT1 = 0x31545844,
		FOURCC_DXT3 = 0x33545844,
		FOURCC_DXT5 = 0x35545844,
	};


	struct DDSHeader
	{
		uint32_t size;
		uint32_t flags;
		uint32_t height;
		uint32_t width;
		uint32_t linearSize;
		uint32_t depth;
		uint32_t mipMapCount;

		uint32_t _reserved[11];

		uint16_t _unussed[3];

		FourCCType fourCC;

		BYTE __unused3[39];
	};

}