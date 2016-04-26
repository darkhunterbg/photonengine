#include "GraphicsService.h"
#include <stddef.h>

namespace photon
{
	graphics::GraphicsService* glGraphicsService = nullptr;

	namespace graphics
	{


		GraphicsService::GraphicsService()
		{
			
		}

		GraphicsService* GraphicsService::Initialize(memory::MemoryStack& stack)
		{
			ASSERT(glGraphicsService == nullptr);

			void* ptr = stack.Allocate(sizeof(GraphicsService));
			glGraphicsService = new(ptr) GraphicsService();

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