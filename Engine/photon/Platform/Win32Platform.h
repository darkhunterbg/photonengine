#pragma once

#include "../Macro.h"
#include "../Platform/Platform.h"

#if PLATFORM == WINDOWS

#include "../Types.h"
#include "Win32GL.h"

namespace photon
{
	struct EXPORT FileHandler
	{
		void* handle;
	};

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

		static FileHandler FileOpen(const wchar_t* path);
		static void FileClose(FileHandler file);
		static size_t GetFileSize(FileHandler file);
		static size_t ReadFromFile(FileHandler file, void* buffer, size_t bufferSize);

		static void DebugLog(const char* msg,...);

	} typedef Platform;
}
#endif