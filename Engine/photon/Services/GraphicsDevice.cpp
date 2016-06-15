#include "GraphicsDevice.h"
#include "../GraphicsAPI/GraphicsAPI.h"

namespace photon
{
	GraphicsDevice::GraphicsDevice(GraphicsAPI* api)
	{

	}

	GraphicsDevice::~GraphicsDevice()
	{
		int count = shaders.Count();
		for (int i = 0; i < count; ++i)
			api->DestroyShader(shaders[i]);

		count = shaderPrograms.Count();
		for (int i = 0; i < count; ++i)
			api->DestoryShaderProgram(shaderPrograms[i]);

		count = vertexBuffers.Count();
		for (int i = 0; i < count; ++i)
			api->DestroyVertexBuffer(vertexBuffers[i]);

		count = vertexBufferBindings.Count();
		for (int i = 0; i < count; ++i)
			api->DestroyVertexBufferBinding(vertexBufferBindings[i]);

		count = uniformBuffers.Count();
		for (int i = 0; i < count; ++i)
			api->DestroyUniformBuffer(uniformBuffers[i]);

		count = indexBuffers.Count();
		for (int i = 0; i < count; ++i)
			api->DestroyIndexBuffer(indexBuffers[i]);

		count = textures.Count();
		for (int i = 0; i < count; ++i)
			api->DestroyTexture(textures[i]);

		count = samplers.Count();
		for (int i = 0; i < count; ++i)
			api->DestroySampler(samplers[i]);
	}

	
	ShaderHandler GraphicsDevice::CreateShader(ShaderType shader, const char* shaderCode)
	{
		ShaderHandler handler = api->CreateShader(shader, shaderCode);
		shaders.Add(handler);
		return handler;
	}
	ShaderProgramHandler GraphicsDevice::CreateShaderProgram(const ShaderHandler* shaders, int count)
	{
		ShaderProgramHandler handler = api->CreateShaderProgram(shaders, count);
		shaderPrograms.Add(handler);
		return handler;
	}
	VertexBufferHandler GraphicsDevice::CreateVertexBuffer(VertexBufferType type,const void* vertices, size_t verticesCount,int vertexSize)
	{
		VertexBufferHandler handler = api->CreateVertexBuffer(type, vertices, verticesCount, vertexSize);
		vertexBuffers.Add(handler);
		return handler;
	}
	VertexBufferBindingHandler GraphicsDevice::CreateVertexBufferBinding(const VertexBufferHandler* vertexBuffers, const VertexBufferLayout* layots, int buffersCount, IndexBufferHandler indexBuffer )
	{
		VertexBufferBindingHandler handler = api->CreateVertexBufferBinding(vertexBuffers, layots, buffersCount, indexBuffer);
		vertexBufferBindings.Add(handler);
		return handler;
	}
	IndexBufferHandler GraphicsDevice::CreateIndexBuffer(const void* indices, size_t indicesCount, IndiceType indiceType)
	{
		IndexBufferHandler handler = api->CreateIndexBuffer(indices, indicesCount, indiceType);
		indexBuffers.Add(handler);
		return handler;
	}
	UniformBufferHandler GraphicsDevice::CreateUniformBuffer(size_t bufferSize, void* bufferValue)
	{
		UniformBufferHandler handler = api->CreateUniformBuffer(bufferSize, bufferValue);
		uniformBuffers.Add(handler);
		return handler;
	}

	TextureHandler GraphicsDevice::LoadTexture(void* data, LoadTextureType type)
	{
		TextureHandler texture;
		switch (type)
		{
		case LoadTextureType::Bitmap:
			texture = api->LoadTextureBitmap(data);
			break;
		case LoadTextureType::DDS:
			texture = api->LoadTextureDDS(data);
		default:
			break;
		}
		textures.Add(texture);
		return texture;
	}
}