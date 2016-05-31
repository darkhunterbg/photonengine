#pragma once



#if defined(_WIN32) || defined(WINDOWS)
#define PLATFORM WINDOWS
#define BUILD_PLATFORM

#define OPENGL 1
//#define DIRECTX 2
#endif

#if defined(__linux__) || defined(LINUX)
#define PLATFORM LINUX
#define OPENGL
#endif

#if !defined(PLATFORM)
#error Unknown build platform!
#endif


#if (PLATFORM == WINDOWS)
#include "Win32Platform.h"
#endif