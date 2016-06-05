#include "GraphicsService.h"
#include <stddef.h>

#include "../Math/Vector.h"
#include "../Alloc.h"

#include "AssetsService.h"

namespace photon
{
	GraphicsService* gl_GraphicsService = nullptr;

	GraphicsService::GraphicsService(GraphicsAPI* api) :
		api(api)
	{
		
	}
	GraphicsService::~GraphicsService()
	{

	}

	GraphicsService* GraphicsService::Initialize(GraphicsAPI* api, MemoryStack& stack)
	{
		ASSERT(gl_GraphicsService == nullptr);
		ASSERT(api);

		gl_GraphicsService = MEM_NEW(stack, GraphicsService)(api);
		gl_GraphicsService->InitializeTechniques();

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

	void GraphicsService::InitializeTechniques()
	{
		TextAsset vsText = gl_AssetsService->GetTextAsset("shader.v");
		TextAsset fsText = gl_AssetsService->GetTextAsset("shader.f");

		ShaderHandler vs = api->CreateShader(ShaderType::VERTEX_SHADER, vsText.text);
		ShaderHandler fs = api->CreateShader(ShaderType::FRAGMENT_SHADER, fsText.text);
		ShaderHandler shaders[] = { vs,fs };

		Technique technique = {};

		technique.program = api->CreateShaderProgram(shaders, 2);
		technique.hasVS = true;
		technique.hasFS = true;

		techniques[++techniquesCount] = technique;
	}
}