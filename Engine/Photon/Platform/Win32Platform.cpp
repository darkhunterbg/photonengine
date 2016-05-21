#include "../PE.h"

#if (PLATFORM == WINDOWS)

#define WIN32_LEAN_AND_MEAN

#include <Windows.h>

#include "Win32Platform.h"

namespace photon
{

	platform::Win32Platfrom* gl_Platform = nullptr;

	namespace platform
	{
		Win32Platfrom* Win32Platfrom::Initialize()
		{
			ASSERT(gl_Platform == nullptr);

			gl_Platform = new Win32Platfrom();

			return gl_Platform;
		}
		void Win32Platfrom::Uninitialize()
		{
			ASSERT(gl_Platform);

			delete gl_Platform;
		}


		void* Win32Platfrom::MemoryAlloc(size_t size)
		{
			return VirtualAlloc(nullptr, size, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
		}

		bool Win32Platfrom::MemoryFree(void* address, size_t size)
		{
			return VirtualFree(address, size, MEM_RELEASE) == 0;
		}

		void Win32Platfrom::ThreadReleaseLock(int threadsCount, ThreadLock& lock)
		{
			ReleaseSemaphore(lock.semaphore, threadsCount, nullptr);
		}
		void Win32Platfrom::ThreadWaitLock(ThreadLock& lock)
		{
			WaitForSingleObject(lock.semaphore, INFINITE);
		}

		void Win32Platfrom::ThreadCreateLock(int threadsCount, ThreadLock* outLock)
		{
			outLock->semaphore = CreateSemaphoreEx(nullptr, 0, 8, nullptr, 0, SEMAPHORE_ALL_ACCESS);
		}
		void Win32Platfrom::ThreadDestroyLock(ThreadLock* lock)
		{
			CloseHandle(lock->semaphore);
		}
		int Win32Platfrom::ThreadInterlockedIncrement(int& var)
		{
			MemoryBarrier();
			return InterlockedIncrement((unsigned long*)&var);
		}
	}

}


#endif