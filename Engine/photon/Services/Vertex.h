#pragma once

#include "../Math/Matrix.h"
#include "../Math/Vector.h"
#include "../Macro.h"
#include "../GraphicsAPI/GraphicsAPI.h"

namespace photon
{
	struct Vertex {
		Vector4 position;
		float texCoordX;
		float texCoordY;
	};

	enum class VertexType
	{
		VERTEX = 0,
	};

	struct EXPORT VertexDescription
	{
		int	 size;
		VertexBufferLayout layout;
	};
}