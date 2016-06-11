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

}