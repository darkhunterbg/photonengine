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

	class EXPORT GraphicsService
	{
		DISABLE_COPY(GraphicsService);

	private:
		static const int MAX_SHADER_PROGRAMS = 128;
		static const int MAX_SHADERS = 128;
		static const int MAX_VERTEX_BUFFERS = 128;
		static const int MAX_VERTEX_BUFFER_BINDINGS = 128;
		static const int MAX_UNIFORM_BUFFERS = 128;
		static const int MAX_INDEX_BUFFERS = 128;
		static const int MAX_TEXTURES = 128;

		static const int MAX_MATERIALS = 2 << 4;
		static const int MAX_GEOMETRIES = 2 << 4;

		static const int MAX_DRAW_COMMANDS = 1024;

		GraphicsAPI* api;
		GraphicsDevice* device;


		Array<TexturedMaterial, MAX_MATERIALS> materials;
		Array<Gemoetry, MAX_GEOMETRIES> geometries;


		Array<DrawCommand, MAX_DRAW_COMMANDS> commands;
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

		TextureHandler LoadTexture(void* data, LoadTextureType type);

		void OnResize(int width, int height);


		void RenderObject(const Matrix& world);
	};

	EXPORT extern GraphicsService* gl_GraphicsService;
}