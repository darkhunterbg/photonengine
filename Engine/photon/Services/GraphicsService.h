#pragma once

#include "../Macro.h"
#include "MemoryStack.h"
#include "GraphicsData.h"
#include "../GraphicsAPI/GraphicsAPI.h"
#include "../GraphicsAPI/GraphicsAPITypes.h"
#include "../Utils/Array.h"
#include "Effect.h"

namespace photon
{
	class GraphicsDevice;

	class EXPORT GraphicsService
	{
		DISABLE_COPY(GraphicsService);

	private:
		static const int MAX_MATERIALS = 2 << 4;
		static const int MAX_GEOMETRIES = 2 << 4;

		static const int MAX_DRAW_COMMANDS = 16;

		GraphicsAPI* api;
		GraphicsDevice* device;

		TestEffect effect;


		Array<TexturedMaterial, MAX_MATERIALS> materials;
		Array<Gemoetry, MAX_GEOMETRIES> geometries;


		Array<DrawInstancesData, MAX_DRAW_COMMANDS> instancesData;
		Array<DrawBucket, MAX_DRAW_COMMANDS> buckets;

		SamplerHandler sampler;

		GraphicsService(GraphicsAPI* api, GraphicsDevice* device);
		~GraphicsService();


		void InitializeTechniques();
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