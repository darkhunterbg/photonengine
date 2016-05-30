#include "GraphicsService.h"
#include <stddef.h>

namespace photon
{
	graphics::GraphicsService* gl_GraphicsService = nullptr;

	namespace graphics
	{
		GraphicsService::GraphicsService()
		{
			
		}

		GraphicsService* GraphicsService::Initialize(memory::MemoryStack& stack)
		{
			ASSERT(gl_GraphicsService == nullptr);

			void* ptr = stack.Allocate(sizeof(GraphicsService));
			gl_GraphicsService = new(ptr) GraphicsService();

			return gl_GraphicsService;
		}
		void GraphicsService::Uninitialize()
		{
			ASSERT(gl_GraphicsService);

			gl_GraphicsService->~GraphicsService();
			gl_GraphicsService = nullptr;
		}

	/*	void GraphicsService::SetCurrentWindow(photon::platform::Window window)
		{
e
		}*/
	}
}