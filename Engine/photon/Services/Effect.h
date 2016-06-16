#pragma once

#include "../Macro.h"
#include "../GraphicsAPI/GraphicsAPI.h"


namespace photon
{
	class GraphicsDevice;

	struct EXPORT TestEffect
	{
		UniformBufferHandler vertexBlock;
		UniformBufferHandler fragmentBlock;

		int texSampler;

		ShaderProgramHandler program;

		void Load(GraphicsAPI& api,GraphicsDevice& device);
	};
}