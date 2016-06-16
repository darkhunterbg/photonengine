#pragma once

#include "../Macro.h"
#include "../GraphicsAPI/GraphicsAPI.h"
#include "../Math/Matrix.h"

namespace photon
{
	enum class LoadTextureType
	{
		Bitmap,
		DDS,
	};

	struct EXPORT ShaderProgram
	{
		ShaderProgramHandler handler;
		uint32_t samplersLocation[4];
	};

	struct EXPORT TexturedMaterial
	{
		TextureHandler diffuse;
	};
	struct EXPORT Gemoetry
	{
		VertexBufferBindingHandler vertexBuffer;
		IndexBufferHandler indexBuffer;
	};

	struct EXPORT DrawInstancesData
	{
		static const int MAX_INSTANCES = 1024;

		Matrix worldMatrix[MAX_INSTANCES];
		int count ;
		int textureID;
	};

	struct EXPORT DrawBucket
	{
		uint32_t key;
		void* data;
	};
}