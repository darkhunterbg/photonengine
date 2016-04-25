#include "GraphicsService.h"
#include <stddef.h>

namespace photon
{
	graphics::GraphicsService* glGraphicsService = nullptr;

	namespace graphics
	{


		GraphicsService::GraphicsService(platform::OpenGLContext* context):
			context(context)
		{
			
		}

		GraphicsService* GraphicsService::Initialize(platform::OpenGLContext* context, memory::MemoryStack& stack)
		{
			ASSERT(glGraphicsService == nullptr);

			void* ptr = stack.Allocate(sizeof(GraphicsService));
			glGraphicsService = new(ptr) GraphicsService(context);

			return glGraphicsService;
		}
		void GraphicsService::Uninitialize()
		{
			ASSERT(glGraphicsService);

			glGraphicsService->~GraphicsService();
			glGraphicsService = nullptr;
		}

	/*	void GraphicsService::SetCurrentWindow(photon::platform::Window window)
		{
e
		}*/
	}
}