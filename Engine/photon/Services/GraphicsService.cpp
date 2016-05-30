#include "GraphicsService.h"
#include <stddef.h>

namespace photon
{
	GraphicsService* gl_GraphicsService = nullptr;

	GraphicsService::GraphicsService(GraphicsAPI* api):
		api(api)
	{

	}

	GraphicsService* GraphicsService::Initialize(GraphicsAPIType apiType,const  void* apiParam, MemoryStack& stack)
	{
		ASSERT(gl_GraphicsService == nullptr);

		GraphicsAPI* api = GraphicsAPI::CreateAPI(apiType, apiParam, stack);

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