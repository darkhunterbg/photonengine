#include "GraphicsService.h"
#include <stddef.h>

#include "../Math/Vector.h"
#include "../Alloc.h"

#include "AssetsService.h"

namespace photon
{
	GraphicsService* gl_GraphicsService = nullptr;

	Vector vertices[] = {
		{-0.5f, -0.5f, 0.0f, 1.0f},
		{0.5f, -0.5f, 0.0f, 1.0f },
		{0.0f,  0.5f, 0.0f, 1.0f },
	};

	VertexBufferBindingHandler vbb;
	VertexBufferHandler vb;
	ProgramBlockHandler pb;

	GraphicsService::GraphicsService(GraphicsAPI* api) :
		api(api)
	{

	}
	GraphicsService::~GraphicsService()
	{
		for (int i = 0; i < techniquesCount; ++i)
		{
			Technique& technique = techniques[i];

			if (technique.hasVS)
				api->DestroyShader(technique.vs);

			if (technique.hasFS)
				api->DestroyShader(technique.fs);

			api->DestoryShaderProgram(technique.program);
		}
	}

	GraphicsService* GraphicsService::Initialize(GraphicsAPI* api, MemoryStack& stack)
	{
		ASSERT(gl_GraphicsService == nullptr);
		ASSERT(api);

		gl_GraphicsService = MEM_NEW(stack, GraphicsService)(api);
		gl_GraphicsService->InitializeTechniques();

		vb = gl_GraphicsService->api->CreateVertexBuffer(vertices, 3, sizeof(Vector));
		VertexBufferLayout layout = {};
		layout.attributesCount = 1;
		VertexAttribute attr[] = { { 0, VertexParamType::FLOAT4 } };
		layout.attributes = attr;
		vbb = gl_GraphicsService->api->CreateVertexBufferBinding(&vb, &layout, 1);
		pb = gl_GraphicsService->api->CreateProgramBlock(gl_GraphicsService->techniques[0].program, "Block", sizeof(Vector), nullptr);

		return gl_GraphicsService;
	}
	void GraphicsService::Uninitialize()
	{
		ASSERT(gl_GraphicsService);

		gl_GraphicsService->api->DestroyVertexBuffer(vb);
		gl_GraphicsService->api->DestroyVertexBufferBinding(vbb);

		gl_GraphicsService->~GraphicsService();
		gl_GraphicsService = nullptr;
	}

	float i = 0;
	int x = 1;

	void GraphicsService::PresentFrame()
	{
		i += x* 0.01;
		if (i > 1 || i < 0)
			x = -x;
		Vector data = {i,i,i,1.0f };

		api->ClearBuffer({ 0,0,0.4f,0 });
		api->UseShaderProgram(techniques[0].program);
		Vector* v = (Vector*)api->StartUpdateProgramBlock(pb);
		*v = data;
		api->EndUpdateProgramBlock();
		//api->SetShaderProgramParam(0, { 1.0f,1.0f,0.0f,1.0f });
		api->UseVertexBufferBinding(vbb);
		api->Draw(PrimitiveType::TRIANGLE_LIST, 3);
		api->ClearVertexBufferBinding();
		api->SwapBuffers();
	}

	void GraphicsService::InitializeTechniques()
	{
		TextAsset vsText = gl_AssetsService->GetTextAsset("shader.v");
		TextAsset fsText = gl_AssetsService->GetTextAsset("shader.f");

		Technique technique = {};

		technique.vs = api->CreateShader(ShaderType::VERTEX_SHADER, vsText.text);
		technique.fs = api->CreateShader(ShaderType::FRAGMENT_SHADER, fsText.text);
		ShaderHandler shaders[] = { technique.vs,technique.fs };

		technique.program = api->CreateShaderProgram(shaders, 2);
		technique.hasVS = true;
		technique.hasFS = true;

		techniques[techniquesCount++] = technique;
	}
}