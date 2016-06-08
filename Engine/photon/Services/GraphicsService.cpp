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
	UniformBufferHandler ub;

	GraphicsService::GraphicsService(GraphicsAPI* api) :
		api(api)
	{

	}
	GraphicsService::~GraphicsService()
	{
		for (int i = 0; i < techniquesCount; ++i)
		{
			Technique& technique = techniques[i];

			for (int j = 0; j < technique.shadersCount; ++i)
			{
				api->DestroyShader(technique.shaders[i]);
			}

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
		ub = gl_GraphicsService->api->CreateUniformBuffer( sizeof(Vector), nullptr);
		gl_GraphicsService->api->BindBufferToProgramBlock(gl_GraphicsService->techniques[0].program, "Block", ub);

		return gl_GraphicsService;
	}
	void GraphicsService::Uninitialize()
	{
		ASSERT(gl_GraphicsService);

		gl_GraphicsService->api->DestroyVertexBuffer(vb);
		gl_GraphicsService->api->DestroyVertexBufferBinding(vbb);
		gl_GraphicsService->api->DestroyUniformBuffer(ub);

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

		Vector* v = (Vector*)api->StartUpdateUniformBuffer(ub);
		*v = data;
		api->EndUpdateUniformBuffer();

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

		technique.shaders[0] = api->CreateShader(ShaderType::VERTEX_SHADER, vsText.text);
		technique.shaders[1] = api->CreateShader(ShaderType::FRAGMENT_SHADER, fsText.text);

		technique.program = api->CreateShaderProgram(technique.shaders, 2);

		techniques[techniquesCount++] = technique;
	}
}