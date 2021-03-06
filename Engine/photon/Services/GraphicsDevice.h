#pragma once


#include "../Macro.h"
#include "../Utils/Array.h"
#include "../GraphicsAPI/GraphicsAPITypes.h"
#include "../GraphicsAPI/GraphicsAPI.h"
#include "GraphicsData.h"

namespace photon
{
	class GraphicsService;

	class  GraphicsDevice
	{
		DISABLE_COPY(GraphicsDevice);


	private:
		static const int MAX_SHADER_PROGRAMS = 128;
		static const int MAX_SHADERS = 128;
		static const int MAX_VERTEX_BUFFERS = 128;
		static const int MAX_VERTEX_BUFFER_BINDINGS = 128;
		static const int MAX_UNIFORM_BUFFERS = 128;
		static const int MAX_INDEX_BUFFERS = 128;
		static const int MAX_TEXTURES = 128;
		static const int MAX_SAMPLERS = 16;
		static const int MAX_STATES = 16;


		Array<ShaderProgramHandler, MAX_SHADER_PROGRAMS> shaderPrograms;
		Array<ShaderHandler, MAX_SHADERS> shaders;
		Array<VertexBufferHandler, MAX_VERTEX_BUFFERS> vertexBuffers;
		Array<VertexBufferBindingHandler, MAX_VERTEX_BUFFER_BINDINGS> vertexBufferBindings;
		Array<UniformBufferHandler, MAX_UNIFORM_BUFFERS> uniformBuffers;
		Array<IndexBufferHandler, MAX_INDEX_BUFFERS> indexBuffers;
		Array<TextureHandler, MAX_TEXTURES> textures;
		Array<SamplerHandler, MAX_SAMPLERS> samplers;

		GraphicsAPI* api;

	public:
		GraphicsDevice(GraphicsAPI* api);
		~GraphicsDevice();

		ShaderProgramHandler CreateShaderProgram(const ShaderHandler* shaders, int count);
		
		VertexBufferBindingHandler CreateVertexBufferBinding(const VertexBufferHandler* vertexBuffers, const VertexBufferLayout* layots, int buffersCount, IndexBufferHandler indexBuffer = IndexBufferHandler::Empty);

		UniformBufferHandler CreateUniformBuffer(size_t bufferSize, void* bufferValue);

		RasterizationStateHandler CreateRasterizationState(FillMode fillMode, CullMode cullMode);

		TextureHandler GetTexture(int textureID);
		ShaderHandler GetShader(int shaderID);
		VertexBufferHandler GetVertexBuffer(int vertexBufferID);
		IndexBufferHandler GetIndexBuffer(int indexBufferID);

		int CreateTexture(void* data, LoadTextureType type);
		int CreateShader(ShaderType type, const char* shaderCode);
		int CreateVertexBuffer(VertexBufferType type, const void* vertices, size_t verticesCount, int vertexSize);
		int CreateIndexBuffer(const void* indices, size_t indicesCount, IndiceType indiceType);

		
	};
}