#pragma once

#include "New.h"
#include "Macro.h"

//============================ Microsoft Visual C =========================

#if defined(__GNUG__)
#define EXPORT
#define ALIGN(alignment) __attribute__ ((aligned ( alignment ) ))
#endif

#if defined(_MSC_VER)

#if defined(ENGINE_EXPORTS)
#define EXPORT _declspec(dllexport)
#else
#define EXPORT _declspec(dllimport)
#endif

#define ALIGN(alignment) _declspec( align( alignment ) )

#endif

//============================ WIN32 =========================

#if defined(_WIN32)
#define PLATFORM WINDOWS
#define BUILD_PLATFORM
#endif

#if defined(__linux__)
#define PLATFORM LINUX
#endif

#if !defined(PLATFORM)
#error Unknown build platform!
#endif


