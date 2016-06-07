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
	
	struct ProgramBlockHandler
	{
		uint32_t ub;
		uint32_t index;
	};

	enum class PrimitiveType : uint32_t
	{
		//Taken directly from OpenGL header
		TRIANGLE_LIST = 0x0004,
		TRIANGLE_STRIP = 0x0005,
		TRIANGLE_FAN = 0x0006
	};
}