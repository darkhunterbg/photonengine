#include "GraphicsService.h"
#include <stddef.h>

#include "../Math/Vector.h"
#include "../Math/Matrix.h"
#include "../Alloc.h"

#include "AssetsService.h"

namespace photon
{
	GraphicsService* gl_GraphicsService = nullptr;


	struct Vertex {
		Vector4 position;
		float texCoordX;
		float texCoordY;
	} vertices[] = {
		{{-1.0f, -1.f, 0.0f, 1.0f}, 0.0f, 1.0f },
		{{ 1.f, -1.f, 0.0f, 1.0f }, 1.0f, 1.0f },
		{{ 1.f,  1.f, 0.0f, 1.0f }, 1.0f, 0.0f },
		{{ -1.f,  1.f, 0.0f, 1.0f }, 0.0f, 0.0f },
	};
	unsigned short indices[] = {
		0,1,3,2
	};

	GraphicsService::GraphicsService(GraphicsAPI* api) :
		api(api)
	{
		RasterizationStateHandler rs = api->CreateRasterizationState(FillMode::SOLID, CullMode::BACK_FACE);
		api->SetRasterizationState(rs);

		BlendStateHandler bs = api->CreateBlendState(true, BlendFactor::SRC_ALPHA, BlendFactor::ONE_MINUS_SRC_ALPHA);
		api->SetBlendState(bs);

		DepthStencilStateHandler dss = api->CreateDepthStencilState(true);
		api->SetDepthStencilState(dss);
	}
	GraphicsService::~GraphicsService()
	{
		int count = shaders.Count();
		for (int i = 0; i < count; ++i)
			api->DestroyShader(shaders[i]);

		count = shaderPrograms.Count();
		for (int i = 0; i < count; ++i)
			api->DestoryShaderProgram(shaderPrograms[i].handler);

		count = vertexBuffers.Count();
		for (int i = 0; i < count; ++i)
			api->DestroyVertexBuffer(vertexBuffers[i]);

		count = vertexBufferBindings.Count();
		for (int i = 0; i < count; ++i)
			api->DestroyVertexBufferBinding(vertexBufferBindings[i]);

		count = uniformBuffers.Count();
		for (int i = 0; i < count; ++i)
			api->DestroyUniformBuffer(uniformBuffers[i]);

		count = indexBuffers.Count();
		for (int i = 0; i < count; ++i)
			api->DestroyIndexBuffer(indexBuffers[i]);

		count = textures.Count();
		for (int i = 0; i < count; ++i)
			api->DestroyTexture(textures[i]);
	}

	GraphicsService* GraphicsService::Initialize(GraphicsAPI* api, MemoryStack& stack)
	{
		ASSERT(gl_GraphicsService == nullptr);
		ASSERT(api);

		gl_GraphicsService = MEM_NEW(stack, GraphicsService)(api);
		gl_GraphicsService->InitializeTechniques();


		VertexBufferLayout layouts[2];

		gl_GraphicsService->indexBuffers.Add(gl_GraphicsService->api->CreateIndexBuffer(indices, 4, IndiceType::USHORT));

		gl_GraphicsService->vertexBuffers.Add(gl_GraphicsService->api->CreateVertexBuffer(VertexBufferType::STATIC, vertices, 4, sizeof(Vertex)));
		layouts[0].attributesCount = 2;
		layouts[0].instance = 0;
		VertexAttribute attr0[] = { { 0, VertexParamType::FLOAT4 },{ 1 , VertexParamType::FLOAT2 } };
		layouts[0].attributes = attr0;

		gl_GraphicsService->vertexBuffers.Add(gl_GraphicsService->api->CreateVertexBuffer(VertexBufferType::DYNAMIC, nullptr, 128, sizeof(Matrix)));
		layouts[1].attributesCount = 4;
		layouts[1].instance = 1;
		VertexAttribute attr1[] = { { 2, VertexParamType::FLOAT4 },{ 3 , VertexParamType::FLOAT4 },{ 4 , VertexParamType::FLOAT4 } ,{ 5 , VertexParamType::FLOAT4 } };
		layouts[1].attributes = attr1;

		gl_GraphicsService->vertexBufferBindings.Add(
			gl_GraphicsService->api->CreateVertexBufferBinding(&gl_GraphicsService->vertexBuffers[0], layouts, 2,
				gl_GraphicsService->indexBuffers[0]));


		gl_GraphicsService->uniformBuffers.Add(gl_GraphicsService->api->CreateUniformBuffer(sizeof(Matrix), nullptr));
		gl_GraphicsService->api->BindBufferToProgramBlock(gl_GraphicsService->shaderPrograms[0].handler, "VertexBlock", 0, gl_GraphicsService->uniformBuffers[0]);

		gl_GraphicsService->uniformBuffers.Add(gl_GraphicsService->api->CreateUniformBuffer(sizeof(Vector4), nullptr));
		gl_GraphicsService->api->BindBufferToProgramBlock(gl_GraphicsService->shaderPrograms[0].handler, "FragmentBlock", 1, gl_GraphicsService->uniformBuffers[1]);

		gl_GraphicsService->sampler = gl_GraphicsService->api->CreateSampler(MinMagFilter::LINEAR_MIPMAP_LINEAR, MinMagFilter::LINEAR, 16.0f);

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

	void GraphicsService::InitializeTechniques()
	{
		TextAsset vsText = gl_AssetsService->GetTextAsset("shader.v");
		TextAsset fsText = gl_AssetsService->GetTextAsset("shader.f");
		TextAsset gsText = gl_AssetsService->GetTextAsset("shader.g");

		ShaderHandler vs = api->CreateShader(ShaderType::VERTEX_SHADER, vsText.text);
		ShaderHandler fs = api->CreateShader(ShaderType::FRAGMENT_SHADER, fsText.text);
		ShaderHandler gs = api->CreateShader(ShaderType::GEOMETRY_SHADER, gsText.text);

		shaders.Add(vs);
		shaders.Add(gs);
		shaders.Add(fs);

		ShaderHandler shaders[] = { vs, gs ,fs };

		ShaderProgram program;
		program.handler = api->CreateShaderProgram(shaders, 3);
		program.samplersLocation[0] = api->GetProgramSamplerLocation(program.handler, "texSampler");
		shaderPrograms.Add(program);
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

	void GraphicsService::OnResize(int width, int height)
	{
		api->SetViewport({ 0,0,width,height });
	}


	void GraphicsService::ExecuteCommads()
	{
		api->ClearFrameBuffer({ 0,0,0.4f, 1 }, 1.0f);

		Vector4* v = (Vector4*)api->StartUpdateUniformBuffer(uniformBuffers[1]);
		*v = { 1,1,1,1 };
		api->EndUpdateUniformBuffer();

		Matrix* m = (Matrix*)api->StartUpdateUniformBuffer(uniformBuffers[0]);

		Matrix view = Matrix::LookAtRH({ 0,0, 10 ,0 }, { 0,0,0,0 }, { 0,1,0,0 });
		Matrix proj = Matrix::PerspectiveRH(PI_OVER_4, 1.0f, 0.01f, 10.0f);

		*m = (view * proj);//.Transpose();
		api->EndUpdateUniformBuffer();

		api->UseShaderProgram(shaderPrograms[0].handler);
		api->UseUniformBuffer(uniformBuffers[0], 0);
		api->UseUniformBuffer(uniformBuffers[1], 1);
		api->UseVertexBufferBinding(vertexBufferBindings[0]);

		api->SetTextureUnitSampler(0, sampler);
		api->UseTexture(textures[0], 0, shaderPrograms[0].samplersLocation[0]);

		int commandsCount = commands.Count();

		Matrix* instances = (Matrix*)api->StartUpdateVertexBuffer(vertexBuffers[1]);
		for (int i = 0; i < commandsCount; ++i)
		{
			*(instances + i) = commands[i].worldMatrix;
		}
		api->EndUpdateVertexBuffer();

		api->DrawIndexedInstanced(PrimitiveType::TRIANGLE_STRIP, photon::IndiceType::USHORT, 4, commandsCount);

		api->ClearVertexBufferBinding();

		commands.Clear();
		buckets.Clear();
	}


	void GraphicsService::RenderObject(const Matrix& world)
	{
		DrawBucket& b = buckets.New();
		b.commandID = commands.Count();
		b.key = buckets.Count();
		DrawCommand& c = commands.New();
		c.worldMatrix = world;
	}
}