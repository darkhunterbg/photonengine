#if defined(__GNUG__)
#define EXPORT
#define ALIGN(alignment) __attribute__ ((aligned ( alignment ) ))
#endif

#if defined(_MSC_VER)

#define _ALLOW_RTCc_IN_STL

#include <intrin.h>

#define BREAKPOINT() __halt()

#if defined(DLL_EXPORT)
#define EXPORT _declspec(dllexport)
#else
#define EXPORT _declspec(dllimport)
#endif

#define ALIGN(alignment) _declspec( align( alignment ) )

#endif


