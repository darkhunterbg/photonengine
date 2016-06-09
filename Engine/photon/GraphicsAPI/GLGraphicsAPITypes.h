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

	//Taken directly from OpenGL header
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
}