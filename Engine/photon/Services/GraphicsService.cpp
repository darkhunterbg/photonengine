#include "GraphicsService.h"
#include <stddef.h>

#include "../Math/Vector.h"
#include "../Math/Matrix.h"
#include "../Alloc.h"

#include "MemoryService.h"
#include "AssetsService.h"
#include "../GraphicsAPI/GraphicsAPI.h"
#include "GraphicsDevice.h"

#include "Effect.h"

namespace photon
{
	GraphicsService* gl_GraphicsService = nullptr;


	GraphicsService::GraphicsService(GraphicsAPI* api, GraphicsDevice* device) :
		api(api), device(device)
	{

		char buffer[1024];
		api->GetVersion(buffer, 1024);
		Platform::DebugLog("API: %s", buffer);

		api->GetDeviceName(buffer, 1024);
		Platform::DebugLog("Device: %s", buffer);

		effectsMemStack = MemoryStack::New(gl_MemoryService->AllocatePage(Megabytes(1)), Megabytes(1));
		bucketsMemStack = MemoryStack::New(gl_MemoryService->AllocatePage(Megabytes(16)), Megabytes(16));

		RasterizationStateHandler rs = api->CreateRasterizationState(FillMode::SOLID, CullMode::BACK_FACE);
		api->SetRasterizationState(rs);

		BlendStateHandler bs = api->CreateBlendState(true, BlendFactor::SRC_ALPHA, BlendFactor::ONE_MINUS_SRC_ALPHA);
		api->SetBlendState(bs);

		DepthStencilStateHandler dss = api->CreateDepthStencilState(true);
		api->SetDepthStencilState(dss);

	}
	GraphicsService::~GraphicsService()
	{
		MemoryStack::Delete(effectsMemStack);
		MemoryStack::Delete(bucketsMemStack);
	}

	GraphicsService* GraphicsService::Initialize(GraphicsAPI* api, MemoryStack& stack)
	{
		ASSERT(gl_GraphicsService == nullptr);
		ASSERT(api);

		GraphicsDevice* device = MEM_NEW(stack, GraphicsDevice)(api);

		gl_GraphicsService = MEM_NEW(stack, GraphicsService)(api, device);
		gl_GraphicsService->InitializeVertexDescriptions();
		gl_GraphicsService->InitializeTechniques();
		gl_GraphicsService->InitializeBuckets();

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

	void GraphicsService::InitializeVertexDescriptions()
	{
		VertexDescription vd;
		vd.size = sizeof(Vertex);
		vd.layout.instance = 0;
		vd.layout.AddAttribute({ 0, VertexParamType::FLOAT4 });
		vd.layout.AddAttribute({ 1, VertexParamType::FLOAT2 });

		vertexDescriptions.Add(vd);
	}
	void GraphicsService::InitializeBuckets()
	{
		instanceBuffer = gl_GraphicsService->api->CreateVertexBuffer(VertexBufferType::DYNAMIC, nullptr, DrawInstancesData::MAX_INSTANCES, sizeof(Matrix));
		instanceBufferLayout.instance = 1;
		instanceBufferLayout.AddAttribute({ 2, VertexParamType::FLOAT4 });
		instanceBufferLayout.AddAttribute({ 3, VertexParamType::FLOAT4 });
		instanceBufferLayout.AddAttribute({ 4, VertexParamType::FLOAT4 });
		instanceBufferLayout.AddAttribute({ 5, VertexParamType::FLOAT4 });

	}
	void GraphicsService::InitializeTechniques()
	{
		effect = MEM_NEW(*effectsMemStack, TestEffect(api, device));
	}


	void GraphicsService::OnResize(int width, int height)
	{
		api->SetViewport({ 0,0,width,height });
	}

	int GraphicsService::CreateTexture(void* data, LoadTextureType type)
	{
		return device->CreateTexture(data, type);
	}
	int GraphicsService::CreateShader(ShaderType type, const char* shaderCode)
	{
		return device->CreateShader(type, shaderCode);
	}
	int GraphicsService::CreateVertexBuffer(VertexType vertexType, const void* vertices, size_t verticesCount)
	{
		const VertexDescription& vb = vertexDescriptions[(int)vertexType];
		return device->CreateVertexBuffer(VertexBufferType::STATIC, vertices, verticesCount, vb.size);
	}
	int GraphicsService::CreateIndexBuffer(const Indice* indices, size_t indicesCount)
	{
		return device->CreateIndexBuffer(indices, indicesCount, IndiceType::USHORT);
	}

	GeometryHandler GraphicsService::CreateGeometry(int vb, int ib, VertexType vertexType)
	{
		ASSERT(vb);
		ASSERT(ib);

		Gemoetry& g = geometries.New();
		VertexBufferHandler vertexBuffer = device->GetVertexBuffer(vb);
		IndexBufferHandler indexBuffer = device->GetIndexBuffer(ib);

		VertexBufferHandler vba[] = { vertexBuffer,instanceBuffer };
		VertexBufferLayout layouts[2];

		layouts[0] = vertexDescriptions[(int)vertexType].layout;
		layouts[1] = instanceBufferLayout;

		g.vertexBufferBinding = device->CreateVertexBufferBinding(vba, layouts, 2, indexBuffer);

		return geometries.Count();
	}
	MaterialHandler GraphicsService::CreateMaterial(int diffuseTextureID)
	{
		ASSERT(diffuseTextureID);

		Material& m = materials.New();
		m.diffuse = device->GetTexture(diffuseTextureID);

		return materials.Count();
	}

	float i = 0;

	void GraphicsService::ExecuteCommads()
	{
		i += 1.0f;

		api->ClearFrameBuffer({ 0,0,0.4f, 1 }, 1.0f);

		effect->UpdateFragmentBlock({ 1,1,1,1 });

		Matrix view = Matrix::LookAtRH({ 0,0,i,0 }, { 0,0,0,0 }, { 0,1,0,0 });
		Matrix proj = Matrix::PerspectiveRH(PI_OVER_4, 1.4f, 0.01f, 10.0f);

		effect->UpdateVertexBlock((view* proj).Transpose());
		effect->Bind();

		api->SetTextureUnitSampler(effect->TEX_SAMPLER_TEX_UNIT, sampler);

		int bucketsCount = buckets.Count();
		for (int i = 0; i < bucketsCount; ++i)
		{
			DrawInstancesData* d = (DrawInstancesData*)buckets[i].data;

			VertexBufferBindingHandler binding = geometries[d->geometry - 1].vertexBufferBinding;
			api->UseVertexBufferBinding(binding);

			TextureHandler texture = materials[d->material - 1].diffuse;;
			effect->SetTexSampler(texture);

			int instancesCount = d->count;


			Matrix* instances = (Matrix*)api->StartUpdateVertexBuffer(instanceBuffer);

			memcpy(instances, d->worldMatrix, sizeof(Matrix)*instancesCount);

			api->EndUpdateVertexBuffer();

			api->DrawIndexedInstanced(PrimitiveType::TRIANGLE_STRIP, photon::IndiceType::USHORT, 4, instancesCount);
		}

		api->ClearVertexBufferBinding();

		buckets.Clear();
		instancesData.Clear();
	}

	void GraphicsService::RenderGeometry(const Matrix& world, GeometryHandler geometry, MaterialHandler material)
	{
		ASSERT(geometry);
		ASSERT(material);

		DrawBucket* b = nullptr;

		int count = buckets.Count();
		for (int i = 0; i < count; ++i)
		{
			DrawInstancesData* d = (DrawInstancesData*)buckets[i].data;
			if (d->material == material && d->geometry == geometry &&
				d->count < d->MAX_INSTANCES)
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
			d->material = material;
			d->geometry = geometry;
			b->data = d;
		}

		DrawInstancesData* data = (DrawInstancesData*)b->data;
		data->worldMatrix[data->count] = world;
		++data->count;

	}
}