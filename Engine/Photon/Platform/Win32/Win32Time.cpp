#include "Win32Time.h"


#if (PLATFORM == WINDOWS)

#include "Win32Platform.h"

namespace photon
{
	namespace platform
	{

		void MeasureTime(TimeMeasure& time)
		{
			QueryPerformanceCounter(&time);
		}


		TimeMeasure SubstractTime(TimeMeasure a, TimeMeasure b)
		{
			TimeMeasure measure;
			measure.QuadPart = a.QuadPart - b.QuadPart;
			return measure;
		}
		TimeMeasure SumTime(TimeMeasure a, TimeMeasure b)
		{
			TimeMeasure measure;
			measure.QuadPart = a.QuadPart + b.QuadPart;
			return measure;
		}

		int64_t TimeToMS(TimeMeasure time)
		{
			LARGE_INTEGER freq;
			QueryPerformanceFrequency(&freq);
			return (1000 * time.QuadPart / freq.QuadPart);
		}
	}

}

#endif