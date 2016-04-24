#pragma once


#include "../../PE.h"


#if (PLATFORM == WINDOWS)

namespace photon
{
	namespace platform
	{
		struct EXPORT OpenGLContext
		{
			void* handle;
		};

		EXPORT OpenGLContext CreateOpenGLContext(void* windowHandle);
		EXPORT bool DeleteOpenGLContext(OpenGLContext context);
	}
}

#endif