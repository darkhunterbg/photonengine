#pragma once

#include "GraphicsAPI.h"
#include "../Platform/Platform.h"

#if GRAPHICS_API == OPENGL

#if PLATFORM == WINDOWS
#include <Windows.h>
#include <GL\glew.h>
#include <gl\GL.h>

#endif


#endif