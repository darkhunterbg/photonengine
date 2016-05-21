#include "JobService.h"
#include <stddef.h>

#include "../Platform.h"

namespace photon
{
	job::JobService* gl_JobService = nullptr;


	namespace job
	{

		JobService::JobService(int threadsCount)
		{
			ASSERT(threadsCount >= 0);

			this->threadsCount = threadsCount;
		}

		JobService* JobService::Initialize(memory::MemoryStack& stack, int threadsCount)
		{
			ASSERT(gl_JobService == nullptr);

			void* ptr = stack.Allocate(sizeof(JobService));
			gl_JobService = new(ptr) JobService(threadsCount);
			gl_Platform->ThreadCreateLock(threadsCount, &gl_JobService->lock);

			return gl_JobService;
		}
		void JobService::Uninitialize()
		{
			ASSERT(gl_JobService);

			gl_Platform->ThreadDestroyLock(&gl_JobService->lock);
			gl_JobService->~JobService();
			gl_JobService = nullptr;
		}

		void JobService::ThreadWork()
		{
			while (true)
			{

				gl_Platform->ThreadWaitLock(gl_JobService->lock);
			}
		}
	}
}