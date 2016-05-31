#pragma once

#include "../Platform/Platform.h"

#if defined(OPENGL)

#define GRAPHICS_API  OPENGL

#include "GLGraphicsAPI.h"

#endif

#if defined(DIRECTX)

#define GRAPHICS_API DIRECTX

#include "DXGraphicsAPI.h"

#endif


#if !defined(GRAPHICS_API)
#error Unknown graphics api!
#endif
