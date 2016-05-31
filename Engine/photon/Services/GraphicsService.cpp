#include "GraphicsService.h"
#include <stddef.h>

namespace photon
{
	GraphicsService* gl_GraphicsService = nullptr;

	GraphicsService::GraphicsService(GraphicsAPI* api):
		api(api)
	{

	}

	GraphicsService* GraphicsService::Initialize(GraphicsAPI* api, MemoryStack& stack)
	{
		ASSERT(gl_GraphicsService == nullptr);
		ASSERT(api);

		void* ptr = stack.Allocate(sizeof(GraphicsService));
		gl_GraphicsService = new(ptr) GraphicsService(api);

		return gl_GraphicsService;
	}
	void GraphicsService::Uninitialize()
	{
		ASSERT(gl_GraphicsService);

		gl_GraphicsService->~GraphicsService();
		gl_GraphicsService = nullptr;
	}

	void GraphicsService::PresentFrame()
	{
		api->SwapBuffers();
	}
}