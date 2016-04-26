#pragma once


#include "../../PE.h"


#if (PLATFORM == WINDOWS)

#include "Win32Platform.h"
#include <stdint.h>


namespace photon
{
	namespace platform
	{

		typedef EXPORT LARGE_INTEGER TimeMeasure;

		EXPORT void MeasureTime(TimeMeasure& time);
		EXPORT TimeMeasure SubstractTime(TimeMeasure a, TimeMeasure b);
		EXPORT TimeMeasure SumTime(TimeMeasure a, TimeMeasure b);
		EXPORT int64_t TimeToMS(TimeMeasure time);
	}
}

#endif