#pragma once

#include "../PE.h"

#if defined( WINDOWS)

#include "../Services/MemoryStack.h"

namespace photon
{
	class EXPORT Win32Game
	{
	private:
		static void CreateAndShowWindow();

		Win32Game() = delete;
		~Win32Game() = delete;
	public:
		static void Initialize(void* hInstnace);
		static void Uninitialize();


		static void Run();
	};
}
#endif