#pragma once


#include "Platform.h"
#include "..\GraphicsAPI\GraphicsAPI.h"

#if GRAPHICS_API == OPENGL
#if PLATFORM == WINDOWS
#include "Win32GL.h"
#endif

#endif