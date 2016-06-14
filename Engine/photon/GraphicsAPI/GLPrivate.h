#pragma once

#include "../Macro.h"

#include "GraphicsAPI.h"

#if GRAPHICS_API == OPENGL

#include "../Platform/PlatformGL.h"
#include "GraphicsAPITypes.h"

namespace photon
{
	namespace gl
	{
		struct EXPORT GLDepthStencilState
		{
			bool depthEnabled;
		};
		struct EXPORT GLRasterizationState
		{
			FillMode fillMode;
			CullMode cullMode;
		};

		struct EXPORT GLBlendingState
		{
			BlendFactor source;
			BlendFactor dest;
			bool enabled;
		
		};

		enum class FourCCType : uint32_t
		{
			FOURCC_DXT1 = 0x31545844,
			FOURCC_DXT3 = 0x33545844,
			FOURCC_DXT5 = 0x35545844,
		};
	}

}

#endif