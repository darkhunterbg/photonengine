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

	VertexBufferHandler vertexBuffer;
	VertexBufferHandler instanceBuffer;
	VertexBufferBindingHandler binding;
	IndexBufferHandler indexBuffer;

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

		gl_GraphicsService->sampler = gl_GraphicsService->api->CreateSampler(MinMagFilter::LINEAR_MIPMAP_LINEAR, MinMagFilter::LINEAR, 16.0f);


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
		effect.Load(*api, *device);
	}

	int GraphicsService::LoadTexture(void* data, LoadTextureType type)
	{
		return device->LoadTexture(data, type);
	}
	int GraphicsService::LoadShader(ShaderType type, const char* code)
	{
		return device->LoadShader(type, code);
	}

	void GraphicsService::OnResize(int width, int height)
	{
		api->SetViewport({ 0,0,width,height });
	}

	void GraphicsService::ExecuteCommads()
	{
		api->ClearFrameBuffer({ 0,0,0.4f, 1 }, 1.0f);

		Vector4* v = (Vector4*)api->StartUpdateUniformBuffer(effect.fragmentBlock);
		*v = { 1,1,1,1 };
		api->EndUpdateUniformBuffer();

		Matrix* m = (Matrix*)api->StartUpdateUniformBuffer(effect.vertexBlock);

		Matrix view = Matrix::LookAtRH({ 0,0, 10 ,0 }, { 0,0,0,0 }, { 0,1,0,0 });
		Matrix proj = Matrix::PerspectiveRH(PI_OVER_4, 1.0f, 0.01f, 10.0f);

		*m = (view * proj);//.Transpose();
		api->EndUpdateUniformBuffer();

		api->UseShaderProgram(effect.program);
		api->UseUniformBuffer(effect.vertexBlock, 0);
		api->UseUniformBuffer(effect.fragmentBlock, 1);
		api->UseVertexBufferBinding(binding);

		api->SetTextureUnitSampler(0, sampler);

		int bucketsCount = buckets.Count();
		for (int i = 0; i < bucketsCount; ++i)
		{
			DrawInstancesData* d = (DrawInstancesData*)buckets[i].data;

			int instancesCount = d->count;
			TextureHandler texture = device->GetTexture(d->textureID);

			api->UseTexture(texture, 0, effect.texSampler);

			Matrix* instances = (Matrix*)api->StartUpdateVertexBuffer(instanceBuffer);

			memcpy(instances, d->worldMatrix, sizeof(Matrix)*instancesCount);

			api->EndUpdateVertexBuffer();

			api->DrawIndexedInstanced(PrimitiveType::TRIANGLE_STRIP, photon::IndiceType::USHORT, 4, instancesCount);
		}

		api->ClearVertexBufferBinding();

		buckets.Clear();
		instancesData.Clear();
	}

	void GraphicsService::RenderObject(const Matrix& world, int textureID)
	{
		DrawBucket* b = nullptr;

		int count = buckets.Count();
		for (int i = 0; i < count; ++i)
		{
			DrawInstancesData* d = (DrawInstancesData*)buckets[i].data;
			if (d->textureID == textureID)
			{
				b = &buckets[i];
				break;
			}
		}
		if (b == nullptr)
		{
			b = &buckets.New();
			DrawInstancesData* d = &instancesData.New();

			d->count = 0;
			d->textureID = textureID;
			b->data = d;
		}


		DrawInstancesData* data = (DrawInstancesData*)b->data;
		data->worldMatrix[data->count] = world;
		++data->count;

	}
}