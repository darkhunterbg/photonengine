#pragma once

#include "../Macro.h"
#include "GraphicsService.h"

namespace photon
{
	typedef uint32_t AssetsHandler;

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
}