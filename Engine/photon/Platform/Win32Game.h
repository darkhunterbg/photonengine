#pragma once

#include "../PE.h"

#if defined( WINDOWS)

#include "../Services/MemoryStack.h"

namespace photon
{
	class EXPORT Win32Game
	{
		DISABLE_COPY(Win32Game);
	private:
		void* hInstance;
		void* hWindow;
		MemoryStack* memStack;

		bool startThreads = false;

		void Win32Init();
		void Win32Uninit();
		void CreateAndShowWindow();

	public:
		Win32Game(void* hInstnace);
		virtual ~Win32Game() = 0;

		void Run();
	};
}
#endif