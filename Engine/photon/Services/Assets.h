#pragma once

#include "../Macro.h"

namespace photon
{
	typedef int AssetsHandler;

	struct EXPORT TextAsset
	{
		char* text;
		size_t textLength;
		AssetsHandler handler;
	};
}