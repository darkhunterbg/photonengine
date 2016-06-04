#pragma once

#include "GraphicsAPI.h"

#if GRAPHICS_API == OPENGL
#include "GLGraphicsAPITypes.h"
#endif
#if GRAPHICS_API == DIRECTX
#include "DXGraphicsAPITypes.h"
#endif

namespace photon
{
	enum  class ShaderType
	{
		VERTEX_SHADER,
		FRAGMENT_SHADER,
	};
}