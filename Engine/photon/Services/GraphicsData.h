#pragma once

#include "../Macro.h"
#include "../GraphicsAPI/GraphicsAPI.h"

namespace photon
{
	enum class LoadTextureType
	{
		Bitmap,
		DDS,
	};

	struct EXPORT ShaderProgram
	{
		ShaderProgramHandler handler;
		uint32_t samplersLocation[4];
	};

}