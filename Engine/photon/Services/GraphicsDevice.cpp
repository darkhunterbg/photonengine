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


	ShaderProgramHandler GraphicsDevice::CreateShaderProgram(const ShaderHandler* shaders, int count)
	{
		ShaderProgramHandler handler = api->CreateShaderProgram(shaders, count);
		shaderPrograms.Add(handler);
		return handler;
	}

	VertexBufferBindingHandler GraphicsDevice::CreateVertexBufferBinding(const VertexBufferHandler* vertexBuffers, const VertexBufferLayout* layots, int buffersCount, IndexBufferHandler indexBuffer )
	{
		VertexBufferBindingHandler handler = api->CreateVertexBufferBinding(vertexBuffers, layots, buffersCount, indexBuffer);
		vertexBufferBindings.Add(handler);
		return handler;
	}
	
	UniformBufferHandler GraphicsDevice::CreateUniformBuffer(size_t bufferSize, void* bufferValue)
	{
		UniformBufferHandler handler = api->CreateUniformBuffer(bufferSize, bufferValue);
		uniformBuffers.Add(handler);
		return handler;
	}

	int GraphicsDevice::LoadTexture(void* data, LoadTextureType type)
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
		return textures.Count() - 1;
	}
	int GraphicsDevice::LoadShader(ShaderType type, const char* shaderCode)
	{
		ShaderHandler handler = api->CreateShader(type, shaderCode);
		shaders.Add(handler);
		return shaders.Count() - 1;
	}
	int GraphicsDevice::LoadVertexBuffer(VertexBufferType type, const void* vertices, size_t verticesCount, int vertexSize)
	{
		VertexBufferHandler handler = api->CreateVertexBuffer(type, vertices, verticesCount, vertexSize);
		vertexBuffers.Add(handler);
		return vertexBuffers.Count()-1;
	}
	int GraphicsDevice::LoadIndexBuffer(const void* indices, size_t indicesCount, IndiceType indiceType)
	{
		IndexBufferHandler handler = api->CreateIndexBuffer(indices, indicesCount, indiceType);
		indexBuffers.Add(handler);
		return indexBuffers.Count() - 1;
	}

	ShaderHandler GraphicsDevice::GetShader(int shaderID)
	{
		return shaders[shaderID];
	}
	TextureHandler GraphicsDevice::GetTexture(int textureID)
	{
		return textures[textureID];
	}
	VertexBufferHandler GraphicsDevice::GetVertexBuffer(int vertexBufferID)
	{
		return vertexBuffers[vertexBufferID];
	}
	IndexBufferHandler GraphicsDevice::GetIndexBuffer(int indexBufferID)
	{
		return indexBuffers[indexBufferID];
	}
}