#include "Macro.h"
#include "New.h"

//============================ Microsoft Visual C =========================

#if defined(__GNUG__)
#define EXPORT
#define ALIGN(alignment) __attribute__ ((aligned ( alignment ) ))
#endif

#if defined(_MSC_VER)

#if defined(PE_EXPORT)
#define EXPORT _declspec(dllexport)
#else
#define EXPORT _declspec(dllimport)
#endif

#define ALIGN(alignment) _declspec( align( alignment ) )

#endif

//============================ WINDOWS =========================

#if defined(_WIN32) || defined(WINDOWS)
#define PE_PLATFORM WINDOWS
#define BUILD_PLATFORM
#endif

#if defined(__linux__) || defined(LINUX)
#define PE_PLATFORM LINUX
#endif

#if !defined(PE_PLATFORM)
#error Unknown build platform!
#endif
