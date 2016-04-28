#pragma once

#include "../PE.h"

#if (PLATFORM == WINDOWS)


namespace photon
{
	namespace platform
	{
		class EXPORT Win32Platfrom
		{
			DISABLE_NEW_DELETE(Win32Platfrom);
			DISABLE_COPY(Win32Platfrom);

		public:
			void* MemoryAlloc(size_t size);
			bool MemoryFree(void* address, size_t size);
		};
	}

	EXPORT extern platform::Win32Platfrom* gl_Platform;
}
#endif