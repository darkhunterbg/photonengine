#pragma once

#include "../Macro.h"
#include "MemoryStack.h"
#include "GraphicsData.h"
#include "../GraphicsAPI/GraphicsAPI.h"
#include "../GraphicsAPI/GraphicsAPITypes.h"
#include "../Utils/Array.h"
#include "GraphicsDevice.h"
#include "Vertex.h"

namespace photon
{
	class GraphicsDevice;
	class TestEffect;


	class EXPORT GraphicsService
	{
		DISABLE_COPY(GraphicsService);

	private:
		static const int MAX_MATERIALS = 2 << 4;
		static const int MAX_GEOMETRIES = 2 << 4;

		static const int MAX_BUCKETS = 1024;
		static const int MAX_UNIQUE_INSTANCES = 128;


		GraphicsAPI* api;
		GraphicsDevice* device;

		TestEffect* effect;

		MemoryStack* effectsMemStack;
		MemoryStack* bucketsMemStack;

		static const int MAX_VERTEX_DESCRIPTIONS = 8;
		Array<VertexDescription, MAX_VERTEX_DESCRIPTIONS> vertexDescriptions;

		//Array<TexturedMaterial, MAX_MATERIALS> materials;
		Array<Gemoetry, MAX_GEOMETRIES> geometries;

		VertexBufferHandler instanceBuffer;
		VertexBufferLayout instanceBufferLayout;

		Array<DrawInstancesData, MAX_UNIQUE_INSTANCES> instancesData;
		Array<DrawBucket, MAX_BUCKETS> buckets;

		SamplerHandler sampler;

		GraphicsService(GraphicsAPI* api, GraphicsDevice* device);
		~GraphicsService();

		void InitializeVertexDescriptions();
		void InitializeTechniques();
		void InitializeBuckets();
	public:
		static GraphicsService* Initialize(GraphicsAPI* api, MemoryStack& stack);
		static void Uninitialize();

		int CreateGeometry(int vb, int ib, VertexType vertexType);
		int CreateTexture(void* data, LoadTextureType type);
		int CreateShader(ShaderType type, const char* shaderCode);
		int CreateVertexBuffer(VertexType vertexType, const void* vertices, size_t verticesCount);
		int CreateIndexBuffer(const void* indices, size_t indicesCount);

		void ExecuteCommads();
		void PresentFrame();


		void OnResize(int width, int height);

		void RenderObject(const Matrix& world, int geometryID, int textureID);
	};

	EXPORT extern GraphicsService* gl_GraphicsService;
}