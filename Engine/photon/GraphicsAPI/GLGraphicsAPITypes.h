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
		uint32_t vao;
		uint32_t vb;
	};
}