#include "GraphicsService.h"
#include <stddef.h>

#include "../Math/Vector.h"
#include "../Math/Matrix.h"
#include "../Alloc.h"

#include "AssetsService.h"
#include "../GraphicsAPI/GraphicsAPI.h"
#include "GraphicsDevice.h"

namespace photon
{
	GraphicsService* gl_GraphicsService = nullptr;

	ShaderProgram program;
	VertexBufferHandler vertexBuffer;
	VertexBufferHandler instanceBuffer;
	VertexBufferBindingHandler binding;
	TextureHandler texture;
	IndexBufferHandler indexBuffer;
	UniformBufferHandler uniformBuffers[2];

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

	GraphicsService::GraphicsService(GraphicsAPI* api, GraphicsDevice* device) :
		api(api), device(device)
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

	}

	GraphicsService* GraphicsService::Initialize(GraphicsAPI* api, MemoryStack& stack)
	{
		ASSERT(gl_GraphicsService == nullptr);
		ASSERT(api);

		GraphicsDevice* device = MEM_NEW(stack, GraphicsDevice)(api);

		gl_GraphicsService = MEM_NEW(stack, GraphicsService)(api, device);
		gl_GraphicsService->InitializeTechniques();

		VertexBufferLayout layouts[2];
		VertexBufferHandler buffers[2];

		indexBuffer = gl_GraphicsService->device->CreateIndexBuffer(indices, 4, IndiceType::USHORT);

		vertexBuffer = gl_GraphicsService->device->CreateVertexBuffer(VertexBufferType::STATIC, vertices, 4, sizeof(Vertex));
		layouts[0].attributesCount = 2;
		layouts[0].instance = 0;
		VertexAttribute attr0[] = { { 0, VertexParamType::FLOAT4 },{ 1 , VertexParamType::FLOAT2 } };
		layouts[0].attributes = attr0;

		instanceBuffer = gl_GraphicsService->api->CreateVertexBuffer(VertexBufferType::DYNAMIC, nullptr, 128, sizeof(Matrix));
		layouts[1].attributesCount = 4;
		layouts[1].instance = 1;
		VertexAttribute attr1[] = { { 2, VertexParamType::FLOAT4 },{ 3 , VertexParamType::FLOAT4 },{ 4 , VertexParamType::FLOAT4 } ,{ 5 , VertexParamType::FLOAT4 } };
		layouts[1].attributes = attr1;

		buffers[0] = vertexBuffer;
		buffers[1] = instanceBuffer;

		binding = gl_GraphicsService->device->CreateVertexBufferBinding(buffers, layouts, 2, indexBuffer);


		uniformBuffers[0] =gl_GraphicsService->device->CreateUniformBuffer(sizeof(Matrix), nullptr);
		gl_GraphicsService->api->BindBufferToProgramBlock(program.handler, "VertexBlock", 0, uniformBuffers[0]);

		uniformBuffers[1] = gl_GraphicsService->device->CreateUniformBuffer(sizeof(Vector4), nullptr);
		gl_GraphicsService->api->BindBufferToProgramBlock(program.handler, "FragmentBlock", 1, uniformBuffers[1]);

		gl_GraphicsService->sampler = gl_GraphicsService->api->CreateSampler(MinMagFilter::LINEAR_MIPMAP_LINEAR, MinMagFilter::LINEAR, 16.0f);

		texture = photon::gl_AssetsService->GetTextureAsset("texture.dds").texture;

		return gl_GraphicsService;
	}
	void GraphicsService::Uninitialize()
	{
		ASSERT(gl_GraphicsService);

		gl_GraphicsService->device->~GraphicsDevice();
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

		ShaderHandler vs = device->CreateShader(ShaderType::VERTEX_SHADER, vsText.text);
		ShaderHandler fs = device->CreateShader(ShaderType::FRAGMENT_SHADER, fsText.text);
		ShaderHandler gs = device->CreateShader(ShaderType::GEOMETRY_SHADER, gsText.text);

		ShaderHandler shaders[] = { vs, gs ,fs };

		program.handler = api->CreateShaderProgram(shaders, 3);
		program.samplersLocation[0] = api->GetProgramSamplerLocation(program.handler, "texSampler");
	}

	TextureHandler GraphicsService::LoadTexture(void* data, LoadTextureType type)
	{
		return device->LoadTexture(data, type);
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

		api->UseShaderProgram(program.handler);
		api->UseUniformBuffer(uniformBuffers[0], 0);
		api->UseUniformBuffer(uniformBuffers[1], 1);
		api->UseVertexBufferBinding(binding);

		api->SetTextureUnitSampler(0, sampler);
		api->UseTexture(texture, 0, program.samplersLocation[0]);

		int commandsCount = commands.Count();

		Matrix* instances = (Matrix*)api->StartUpdateVertexBuffer(instanceBuffer);
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