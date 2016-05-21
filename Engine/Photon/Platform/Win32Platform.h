#pragma once

#include "../PE.h"

#if (PLATFORM == WINDOWS)


namespace photon
{
	namespace platform
	{
		struct ThreadLock
		{
			void* semaphore;
		} typedef Win32ThreadLock;

		class EXPORT Win32Platfrom
		{
			DISABLE_COPY(Win32Platfrom);
		private:
			Win32Platfrom() = default;
			~Win32Platfrom() = default;
		public:
			void* MemoryAlloc(size_t size);
			bool MemoryFree(void* address, size_t size);

			void ThreadReleaseLock(int threadsCount, ThreadLock& lock);
			void ThreadWaitLock(ThreadLock& lock);
			void ThreadCreateLock(int threadsCount, ThreadLock* outLock);
			void ThreadDestroyLock(ThreadLock* lock);

			static Win32Platfrom* Initialize();
			static void Uninitialize();
		};
	}

	EXPORT extern platform::Win32Platfrom* gl_Platform;
}
#endif