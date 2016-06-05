#pragma once

#include "../Macro.h"
#include "../Platform/Platform.h"
#include "../Types.h"

#if PLATFORM == WINDOWS


namespace photon
{

	class EXPORT Win32Game
	{
	private:
		static void CreateAndShowWindow();

		Win32Game() = delete;
		~Win32Game() = delete;
	public:
		static void Initialize(void* hInstnace, const TCHAR* assetsPath);
		static void Uninitialize();


		static void Run();
	};
}
#endif