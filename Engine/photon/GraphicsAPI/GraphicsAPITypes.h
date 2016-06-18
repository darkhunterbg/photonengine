#pragma once

#include "../Platform/Platform.h"

#if defined(OPENGL)
#include "GLGraphicsAPITypes.h"
#endif
#if defined(DIRECTX)
#include "DXGraphicsAPITypes.h"
#endif

namespace photon
{
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
		static const int MAX_ATTRIBUTES = 8;

		int attributesCount = 0;
		int instance;

		VertexAttribute attributes[MAX_ATTRIBUTES];

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

		inline void AddAttribute(const VertexAttribute& attr)
		{
			attributes[attributesCount++] = attr;
		}

	
	};

	
	struct  Viewport
	{
		int x, y, width, height;
	};
}