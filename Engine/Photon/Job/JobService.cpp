#include "JobService.h"
#include <stddef.h>

#include "../Platform.h"

namespace photon
{
	job::JobService* gl_JobService = nullptr;


	namespace job
	{
		Job::Job()
		{
			Reset();
		}
		void Job::AddWork(WorkAction action, void* param)
		{
			ASSERT(workCount < 1000);
			work[workCount].action = action;
			work[workCount].param = param;
			++workCount;
		}
		void Job::Reset()
		{
			workCount = 0;
			completedWork = 0;
		}


		//==================================================================================

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
				gl_JobService->ProcessJob(gl_JobService->job);
				gl_Platform->ThreadInterlockedIncrement(gl_JobService->completedThreadsCount);
			}
		}

		Job& JobService::NewJob()
		{
			job.Reset();
			return job;
		}
		void JobService::CompleteJob(Job& job)
		{
			completedThreadsCount = 0;
			gl_Platform->ThreadReleaseLock(threadsCount, lock);
			ProcessJob(job);

			while (completedThreadsCount< threadsCount);
		}
		void JobService::ProcessJob(Job& job)
		{
			int count = job.workCount;

			int workIndex = gl_Platform->ThreadInterlockedIncrement(job.completedWork);
			while (workIndex < job.workCount)
			{
				Work work = job.work[workIndex];
				work.action(work.param);
				workIndex = gl_Platform->ThreadInterlockedIncrement(job.completedWork);
			}

		}
	}
}