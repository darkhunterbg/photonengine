#pragma once

//============================ Microsoft Visual C =========================

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


#if !defined(PLATFORM)
#error Unknown build platform!
#endif


#define Kilobytes(val) val * 1024
#define Megabytes(val) val * 1024 * 1024
#define Gigabytes(val) val * 1024 * 1024 * 1024
