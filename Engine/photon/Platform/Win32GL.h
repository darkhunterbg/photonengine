#pragma once

#include "../PE.h"

#if defined(WINDOWS)
namespace photon
{
	//Types are directly taken from https://msdn.microsoft.com/en-us/library/windows/desktop/aa383751(v=vs.85).aspx
	struct GLContext
	{
		void* hdc;
		void* hgldc;
	} typedef Win32GLContext;

	struct GLCreateParam
	{
		void* hwindow;
	};
}
#endif