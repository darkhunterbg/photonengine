#pragma once

#include "../Macro.h"
#include "../Platform/Platform.h"

#if PLATFORM == WINDOWS

#include "Win32GL.h"

namespace photon
{
	class EXPORT Win32Platfrom
	{
	private:
		static bool initialized;

		Win32Platfrom() = delete;
		~Win32Platfrom() = delete;
	public:
		static void* MemoryAlloc(size_t size);
		static bool MemoryFree(void* address, size_t size);

		static void Initialize();
		static void Uninitialize();

		static GLContext GLCreateContext(GLCreateParam param);
		static void GLDestroyContext(GLContext context);
		static void GLSwapBuffers(GLContext context);

	} typedef Platform;
}
#endif