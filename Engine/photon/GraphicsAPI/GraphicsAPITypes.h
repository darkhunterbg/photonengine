#pragma once

#include "GraphicsAPI.h"

#if GRAPHICS_API == OPENGL
#include "GLGraphicsAPITypes.h"
#endif
#if GRAPHICS_API == DIRECTX
#include "DXGraphicsAPITypes.h"
#endif

namespace photon
{
	enum  class ShaderType
	{
		VERTEX_SHADER,
		FRAGMENT_SHADER,
	};

	enum  class VertexParamType 
	{
		FLOAT ,
		FLOAT2,
		FLOAT3,
		FLOAT4
	};

	struct VertexAttribute
	{
		int location;
		VertexParamType type;

	};

	struct VertexBufferLayout
	{
		VertexAttribute* attributes;
		int attributesCount;
		int instance;

		size_t GetTotalSize() const
		{
			size_t size = 0;

			for (int j = 0; j < attributesCount; ++j)
			{

				switch (attributes[j].type)
				{
				case VertexParamType::FLOAT:
					size += sizeof(float);
					break;
				case VertexParamType::FLOAT2:
					size += sizeof(float) * 2;
					break;
				case VertexParamType::FLOAT3:
					size += sizeof(float) * 3;
					break;
				case VertexParamType::FLOAT4:
					size += sizeof(float) * 4;
					break;
				default:
					break;
				}
			}
			return size;

		}

	
	};

	
	struct  Viewport
	{
		int x, y, width, height;
	};
}