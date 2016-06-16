#pragma once

#include "../Macro.h"
#include "MemoryStack.h"
#include "GraphicsData.h"
#include "../GraphicsAPI/GraphicsAPI.h"
#include "../GraphicsAPI/GraphicsAPITypes.h"
#include "../Utils/Array.h"

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

		//Array<TexturedMaterial, MAX_MATERIALS> materials;
		//Array<Gemoetry, MAX_GEOMETRIES> geometries;
		VertexBufferHandler instanceBuffer;

		typedef Array<DrawInstancesData, MAX_UNIQUE_INSTANCES> DrawInstanceDataArray;
		DrawInstanceDataArray* instancesData;

		typedef Array<DrawBucket, MAX_BUCKETS> DrawBucketArray;
		DrawBucketArray* buckets;

		SamplerHandler sampler;

		GraphicsService(GraphicsAPI* api, GraphicsDevice* device);
		~GraphicsService();


		void InitializeTechniques();
		void InitializeBuckets();
	public:
		static GraphicsService* Initialize(GraphicsAPI* api, MemoryStack& stack);
		static void Uninitialize();

		void ExecuteCommads();
		void PresentFrame();

		int LoadShader(ShaderType type, const char* code);
		int LoadTexture(void* data, LoadTextureType type);

		void OnResize(int width, int height);

		void RenderObject(const Matrix& world, int textureID);
	};

	EXPORT extern GraphicsService* gl_GraphicsService;
}