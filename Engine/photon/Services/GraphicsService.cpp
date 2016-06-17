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
	void GraphicsService::InitializeBuckets()
	{
		instancesData = MEM_NEW(*bucketsMemStack, DrawInstanceDataArray)();
		buckets = MEM_NEW(*bucketsMemStack, DrawBucketArray)();

		instanceBuffer = gl_GraphicsService->api->CreateVertexBuffer(VertexBufferType::DYNAMIC, nullptr, DrawInstancesData::MAX_INSTANCES, sizeof(Matrix));

	}
	void GraphicsService::InitializeTechniques()
	{
		effect = MEM_NEW(*effectsMemStack, TestEffect(api, device));
	}

	GraphicsDevice& GraphicsService::GetDevice()
	{
		return *device;
	}

	void GraphicsService::OnResize(int width, int height)
	{
		api->SetViewport({ 0,0,width,height });
	}

	int GraphicsService::CreateGeometry(int vb, int ib, VertexBufferLayout layout)
	{
		Gemoetry& g = geometries.New();
		VertexBufferHandler vertexBuffer = device->GetVertexBuffer(vb);
		IndexBufferHandler indexBuffer = device->GetIndexBuffer(ib);

		VertexBufferHandler vba[] = { vertexBuffer,instanceBuffer };
		VertexBufferLayout layouts[2];

		layouts[0] = layout;

		layouts[1].attributesCount = 4;
		layouts[1].instance = 1;
		VertexAttribute attr1[] = { { 2, VertexParamType::FLOAT4 },{ 3 , VertexParamType::FLOAT4 },{ 4 , VertexParamType::FLOAT4 } ,{ 5 , VertexParamType::FLOAT4 } };
		layouts[1].attributes = attr1;

		g.vertexBufferBinding = device->CreateVertexBufferBinding(vba, layouts, 2, indexBuffer);

		return geometries.Count() - 1;
	}

	void GraphicsService::ExecuteCommads()
	{
		api->ClearFrameBuffer({ 0,0,0.4f, 1 }, 1.0f);

		effect->UpdateFragmentBlock({ 1,1,1,1 });

		Matrix view = Matrix::LookAtRH({ 0,0, 10 ,0 }, { 0,0,0,0 }, { 0,1,0,0 });
		Matrix proj = Matrix::PerspectiveRH(PI_OVER_4, 1.0f, 0.01f, 10.0f);

		effect->UpdateVertexBlock(view * proj);
		effect->Bind();

		api->SetTextureUnitSampler(effect->TEX_SAMPLER_TEX_UNIT, sampler);

		int bucketsCount = buckets->Count();
		for (int i = 0; i < bucketsCount; ++i)
		{
			DrawInstancesData* d = (DrawInstancesData*)buckets->Get(i).data;

			VertexBufferBindingHandler binding = geometries[d->geometryID].vertexBufferBinding;
			api->UseVertexBufferBinding(binding);


			int instancesCount = d->count;
			TextureHandler texture = device->GetTexture(d->textureID);

			effect->SetTexSampler(texture);

			Matrix* instances = (Matrix*)api->StartUpdateVertexBuffer(instanceBuffer);

			memcpy(instances, d->worldMatrix, sizeof(Matrix)*instancesCount);

			api->EndUpdateVertexBuffer();

			api->DrawIndexedInstanced(PrimitiveType::TRIANGLE_STRIP, photon::IndiceType::USHORT, 4, instancesCount);
		}

		api->ClearVertexBufferBinding();

		buckets->Clear();
		instancesData->Clear();
	}

	void GraphicsService::RenderObject(const Matrix& world, int geometryID, int textureID)
	{
		DrawBucket* b = nullptr;

		int count = buckets->Count();
		for (int i = 0; i < count; ++i)
		{
			DrawInstancesData* d = (DrawInstancesData*)buckets->Get(i).data;
			if (d->textureID == textureID && d->geometryID == geometryID)
			{
				b = &buckets->Get(i);
				break;
			}
		}
		if (b == nullptr)
		{
			b = &buckets->New();
			DrawInstancesData* d = &instancesData->New();

			d->count = 0;
			d->textureID = textureID;
			d->geometryID = geometryID;
			b->data = d;
		}


		DrawInstancesData* data = (DrawInstancesData*)b->data;
		data->worldMatrix[data->count] = world;
		++data->count;

	}
}