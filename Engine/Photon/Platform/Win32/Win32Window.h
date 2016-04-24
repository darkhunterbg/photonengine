#pragma once


#include "../../PE.h"

#if (PLATFORM == WINDOWS)

struct HGLRC;

namespace photon
{
	namespace platform
	{
		struct Window
		{
			void* handle;
		};
	}
}

#endif