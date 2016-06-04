#pragma once

#include "Platform\Platform.h"

#if PLATFORM == WINDOWS
#if !defined(WINDEF)
typedef wchar_t TCHAR;
#endif
#endif

typedef unsigned char BYTE;