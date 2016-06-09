#include "GraphicsService.h"
#include <stddef.h>

#include "../Math/Vector.h"
#include "../Alloc.h"

#include "AssetsService.h"

namespace photon
{
	GraphicsService* gl_GraphicsService = nullptr;


	struct Vertex {
		Vector position;
		float texCoordX;
		float texCoordY;
	} vertices[] = {
		{{-0.5f, -0.5f, 0.0f, 1.0f}, 0.0f, 1.0f },
		{{ 0.5f, -0.5f, 0.0f, 1.0f }, 1.0f, 1.0f },
		{{ 0.5f,  0.5f, 0.0f, 1.0f }, 1.0f, 0.0f },
		{{ -0.5f,  0.5f, 0.0f, 1.0f }, 0.0f, 0.0f },
	};
	unsigned short indices[] = {
		0,1,3,2
	};

	GraphicsService::GraphicsService(GraphicsAPI* api) :
		api(api)
	{

	}
	GraphicsService::~GraphicsService()
	{
		int count = shaders.GetCount();
		for (int i = 0; i < count; ++i)
			api->DestroyShader(shaders[i]);

		count = shaderPrograms.GetCount();
		for (int i = 0; i < count; ++i)
			api->DestoryShaderProgram(shaderPrograms[i]);

		count = vertexBuffers.GetCount();
		for (int i = 0; i < count; ++i)
			api->DestroyVertexBuffer(vertexBuffers[i]);

		count = vertexBufferBindings.GetCount();
		for (int i = 0; i < count; ++i)
			api->DestroyVertexBufferBinding(vertexBufferBindings[i]);

		count = uniformBuffers.GetCount();
		for (int i = 0; i < count; ++i)
			api->DestroyUniformBuffer(uniformBuffers[i]);

		count = indexBuffers.GetCount();
		for (int i = 0; i < count; ++i)
			api->DestroyIndexBuffer(indexBuffers[i]);

		count = textures.GetCount();
		for (int i = 0; i < count; ++i)
			api->DestroyTexture(textures[i]);
	}

	GraphicsService* GraphicsService::Initialize(GraphicsAPI* api, MemoryStack& stack)
	{
		ASSERT(gl_GraphicsService == nullptr);
		ASSERT(api);

		gl_GraphicsService = MEM_NEW(stack, GraphicsService)(api);
		gl_GraphicsService->InitializeTechniques();

		gl_GraphicsService->indexBuffers.Add(gl_GraphicsService->api->CreateIndexBuffer(indices, 4, IndiceType::USHORT));
		gl_GraphicsService->vertexBuffers.Add(gl_GraphicsService->api->CreateVertexBuffer(vertices, 4, sizeof(Vertex)));
		VertexBufferLayout layout = {};
		layout.attributesCount = 2;
		VertexAttribute attr[] = { { 0, VertexParamType::FLOAT4 }, { 1 , VertexParamType::FLOAT2 } };
		layout.attributes = attr;
		gl_GraphicsService->vertexBufferBindings.Add(
			gl_GraphicsService->api->CreateVertexBufferBinding(&gl_GraphicsService->vertexBuffers[0], &layout, 1,
				gl_GraphicsService->indexBuffers[0]));
		gl_GraphicsService->uniformBuffers.Add(gl_GraphicsService->api->CreateUniformBuffer(sizeof(Vector), nullptr));
		gl_GraphicsService->api->BindBufferToProgramBlock(gl_GraphicsService->shaderPrograms[0], 0, gl_GraphicsService->uniformBuffers[0]);

		return gl_GraphicsService;
	}
	void GraphicsService::Uninitialize()
	{
		ASSERT(gl_GraphicsService);

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
		Vector data = { i,i,i,1.0f };

		api->ClearBuffer({ 0,0,0.4f,0 });

		api->UseShaderProgram(shaderPrograms[0]);

		Vector* v = (Vector*)api->StartUpdateUniformBuffer(uniformBuffers[0]);
		*v = data;
		api->EndUpdateUniformBuffer();

		api->UseVertexBufferBinding(vertexBufferBindings[0]);
		api->UseTexture(textures[0], 0, shaderPrograms[0]);
		api->DrawIndexed(PrimitiveType::TRIANGLE_STRIP, photon::IndiceType::USHORT, 4);
		api->ClearVertexBufferBinding();

		api->SwapBuffers();
	}

	void GraphicsService::InitializeTechniques()
	{
		TextAsset vsText = gl_AssetsService->GetTextAsset("shader.v");
		TextAsset fsText = gl_AssetsService->GetTextAsset("shader.f");

		ShaderHandler vs = api->CreateShader(ShaderType::VERTEX_SHADER, vsText.text);
		ShaderHandler ps = api->CreateShader(ShaderType::FRAGMENT_SHADER, fsText.text);

		shaders.Add(vs);
		shaders.Add(ps);

		ShaderHandler shaders[] = { vs,ps };

		shaderPrograms.Add(api->CreateShaderProgram(shaders, 2));
	}

	TextureHandler GraphicsService::LoadTexture(void* data, LoadTextureType type)
	{
		TextureHandler texture;
		switch (type)
		{
		case LoadTextureType::Bitmap:
			texture = api->LoadTextureBitmap(data);
			break;
		case LoadTextureType::DDS:
			texture = api->LoadTextureDDS(data);
		default:
			break;
		}
		textures.Add(texture);
		return texture;
	}
}