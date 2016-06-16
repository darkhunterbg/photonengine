#include "Effect.h"
#include "GraphicsDevice.h"

#include "../Math/Matrix.h"
#include "../Math/Vector.h"

#include "AssetsService.h"

namespace photon
{
	void TestEffect::Load(GraphicsAPI& api, GraphicsDevice& device)
	{

		int vsID = gl_AssetsService->GetShaderAsset("shader.v").shaderID;
		int fsID = gl_AssetsService->GetShaderAsset("shader.f").shaderID;
		int gsID = gl_AssetsService->GetShaderAsset("shader.g").shaderID;


		ShaderHandler shaders[] = { 
			device.GetShader(vsID),
			device.GetShader(fsID),
			device.GetShader(gsID)
			 };

		program = api.CreateShaderProgram(shaders, 3);


		vertexBlock = device.CreateUniformBuffer(sizeof(Matrix), nullptr);
		fragmentBlock = device.CreateUniformBuffer(sizeof(Vector4), nullptr);
		api.BindBufferToProgramBlock(program, "VertexBlock", 0, vertexBlock);
		api.BindBufferToProgramBlock(program, "FragmentBlock", 1, fragmentBlock);
		texSampler = api.GetProgramSamplerLocation(program, "texSampler");
	}
}