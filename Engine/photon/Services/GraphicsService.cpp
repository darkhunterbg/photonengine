#include "GraphicsService.h"
#include <stddef.h>

#include "../Math/Vector.h"
#include "../Alloc.h"

namespace photon
{
	GraphicsService* gl_GraphicsService = nullptr;

	GraphicsService::GraphicsService(GraphicsAPI* api) :
		api(api)
	{
		ShaderHandler vs = api->CreateShader(ShaderType::VERTEX_SHADER, "void main(){ vec4 a = gl_Vertex; a.x = a.x * 0.5; a.y = a.y * 0.5; gl_Position = gl_ModelViewProjectionMatrix * a;}");

		api->CreateShaderProgram(&vs, 1);
	}
	GraphicsService::~GraphicsService()
	{

	}

	GraphicsService* GraphicsService::Initialize(GraphicsAPI* api, MemoryStack& stack)
	{
		ASSERT(gl_GraphicsService == nullptr);
		ASSERT(api);

		gl_GraphicsService = MEM_NEW(stack, GraphicsService)(api);

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
		api->ClearBuffer({ 0,0,0,1 });
		api->SwapBuffers();
	}
}