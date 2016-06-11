#pragma once

#include "../Macro.h"
#include "MemoryStack.h"
#include "../GraphicsAPI/GraphicsAPI.h"
#include "../GraphicsAPI/GraphicsAPITypes.h"
#include "../Utils/Array.h"

namespace photon
{
	enum class LoadTextureType
	{
		Bitmap,
		DDS,
	};

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

		GraphicsAPI* api;

		Array<ShaderProgramHandler, MAX_SHADER_PROGRAMS> shaderPrograms;
		Array<ShaderHandler, MAX_SHADERS> shaders;
		Array<VertexBufferHandler, MAX_VERTEX_BUFFERS> vertexBuffers;
		Array<VertexBufferBindingHandler, MAX_VERTEX_BUFFER_BINDINGS> vertexBufferBindings;
		Array<UniformBufferHandler, MAX_UNIFORM_BUFFERS> uniformBuffers;
		Array<IndexBufferHandler, MAX_INDEX_BUFFERS> indexBuffers;
		Array<TextureHandler, MAX_TEXTURES> textures;

		GraphicsService(GraphicsAPI* api);
		~GraphicsService();


		void InitializeTechniques();
	public:
		static GraphicsService* Initialize(GraphicsAPI* api, MemoryStack& stack);
		static void Uninitialize();

		void PresentFrame();

		TextureHandler LoadTexture(void* data, LoadTextureType type);

		void OnResize(int width, int height);
	};

	EXPORT extern GraphicsService* gl_GraphicsService;
}