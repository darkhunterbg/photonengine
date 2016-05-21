#pragma once

#include "../PE.h"
#include "../Memory/MemoryStack.h"
#include "../Platform.h"

#include <stddef.h>	

namespace photon
{
	namespace job
	{
	

		class EXPORT JobService
		{
			DISABLE_NEW_DELETE(GraphicsService);
			DISABLE_COPY(JobService);

		private:
			int threadsCount;
			photon::platform::ThreadLock lock;

			JobService(int threadsCount);
		public:
			static JobService* Initialize(memory::MemoryStack& stack, int threadsCount);
			static void Uninitialize();

			static void ThreadWork();
		};
	}

	EXPORT extern job::JobService* gl_JobService;

}