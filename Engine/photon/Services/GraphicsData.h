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

	typedef unsigned short Indice;
	
	typedef int MaterialHandler;
	struct EXPORT Material
	{
		TextureHandler diffuse;
	};

	typedef int GeometryHandler;
	struct EXPORT Gemoetry
	{
		VertexBufferBindingHandler vertexBufferBinding;
	};

	struct EXPORT DrawInstancesData
	{
		static const int MAX_INSTANCES = 1024;

		Matrix worldMatrix[MAX_INSTANCES];
		int count ;
		MaterialHandler material;
		GeometryHandler geometry;

	};

	struct EXPORT DrawBucket
	{
		uint32_t key;
		void* data;
	};
}