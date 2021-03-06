#pragma once

#include "../Macro.h"

#include <stdint.h>

namespace photon
{
	struct ShaderHandler
	{
		uint32_t shader;
	};
	struct ShaderProgramHandler
	{
		uint32_t program;
	};
	struct VertexBufferHandler
	{
		uint32_t vb;
	};
	struct VertexBufferBindingHandler
	{
		uint32_t vao;
	};
	struct UniformBufferHandler
	{
		uint32_t ub;
	};
	struct IndexBufferHandler
	{
		uint32_t ib;

		static const IndexBufferHandler Empty;
	};
	struct TextureHandler
	{
		uint32_t texture;
	};

	struct DepthStencilStateHandler
	{
		uint32_t id;
	};
	struct RasterizationStateHandler
	{
		uint32_t id;
	};
	struct BlendStateHandler
	{
		uint32_t id;
	};
	struct SamplerHandler
	{
		uint32_t id;
	};

	//Taken directly from OpenGL/glew header
	//TODO: Verify values are the same across platforms
	enum class PrimitiveType : uint32_t
	{
		TRIANGLE_LIST = 0x0004,
		TRIANGLE_STRIP = 0x0005,
		TRIANGLE_FAN = 0x0006
	};
	enum class IndiceType : uint32_t
	{
		USHORT = 0x1403,
		UINT = 0x1405,
	};
	enum class CullMode
	{
		NONE = 0,
		FRONT_FACE = 0x0404,
		BACK_FACE = 0x0405
	};
	enum class FillMode
	{
		WIREFRAME = 0x1B01,
		SOLID = 0x1B02
	};
	enum class BlendFactor
	{
		ZERO = 0,
		ONE = 1,
		SRC_ALPHA = 0x0302,
		DST_ALPHA = 0x0304,
		ONE_MINUS_SRC_ALPHA = 0x0303,
		ONE_MINUS_DST_ALPHA = 0x0305
	};
	enum class VertexBufferType
	{
		STATIC = 0x88E4,
		DYNAMIC = 0x88E8
	};
	enum class ShaderType
	{
		VERTEX_SHADER = 0x8B31,
		FRAGMENT_SHADER = 0x8B30,
		GEOMETRY_SHADER = 0x8DD9,
	};
	enum class MinMagFilter
	{
		NEAREST = 0x2600,
		LINEAR = 0x2601,
		NEAREST_MIPMAP_NEAREST = 0x2700,
		LINEAR_MIPMAP_NEAREST = 0x2701,
		NEAREST_MIPMAP_LINEAR = 0x2702,
		LINEAR_MIPMAP_LINEAR = 0x2703,
	};

}