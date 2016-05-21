#pragma once

#include "../PE.h"
#include "../Memory/MemoryStack.h"
#include "../Platform.h"

#include <stddef.h>	

namespace photon
{
	namespace job
	{
	
		class EXPORT JobService;
		typedef void(*WorkAction)(void*);

		struct Work
		{
			WorkAction action;
			void* param;
		};

		class EXPORT Job
		{
			DISABLE_NEW_DELETE(Job);
			DISABLE_COPY(Job);

			friend class JobService;
		private:
			int workCount;
			int completedWork;
			Work work[1024];
		public:
			Job();
			void AddWork(WorkAction action, void* param);
			void Reset();
		};

		class EXPORT JobService
		{
			DISABLE_NEW_DELETE(GraphicsService);
			DISABLE_COPY(JobService);

		private:
			int threadsCount;
			int completedThreadsCount = 0;
			photon::platform::ThreadLock lock;
			Job job;
			JobService(int threadsCount);
		public:
			static JobService* Initialize(memory::MemoryStack& stack, int threadsCount);
			static void Uninitialize();
			static void ThreadWork();

			void ProcessJob(Job& job);

			Job& NewJob();
			void CompleteJob(Job& job);
		};
	}

	EXPORT extern job::JobService* gl_JobService;

}