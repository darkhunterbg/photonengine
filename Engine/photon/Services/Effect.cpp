#include "Effect.h"
#include "GraphicsDevice.h"

#include "../Math/Matrix.h"
#include "../Math/Vector.h"

#include "AssetsService.h"

namespace photon
{
	TestEffect::TestEffect(GraphicsAPI* api, GraphicsDevice* device) :Effect(api)
	{
		int vsID = gl_AssetsService->GetShaderAsset("shader.v").shaderID;
		int fsID = gl_AssetsService->GetShaderAsset("shader.f").shaderID;
		int gsID = gl_AssetsService->GetShaderAsset("shader.g").shaderID;


		ShaderHandler shaders[] = { 
			device->GetShader(vsID),
			device->GetShader(fsID),
			device->GetShader(gsID)
			 };

		program = api->CreateShaderProgram(shaders, 3);

		vertexBlock = device->CreateUniformBuffer(sizeof(Matrix), nullptr);
		fragmentBlock = device->CreateUniformBuffer(sizeof(Vector4), nullptr);
		api->BindBufferToProgramBlock(program, "VertexBlock", 0, vertexBlock);
		api->BindBufferToProgramBlock(program, "FragmentBlock", 1, fragmentBlock);
		texSampler = api->GetProgramSamplerLocation(program, "texSampler");
	}

	void TestEffect::UpdateVertexBlock(const Matrix& matrix)
	{
		Matrix* m = (Matrix*)api->StartUpdateUniformBuffer(vertexBlock);
		*m = matrix;
		api->EndUpdateUniformBuffer();
	}
	void TestEffect::UpdateFragmentBlock( const Vector4& vector)
	{
		Vector4* m = (Vector4*)api->StartUpdateUniformBuffer(fragmentBlock);
		*m = vector;
		api->EndUpdateUniformBuffer();
	}

	void TestEffect::Bind()
	{
		api->UseShaderProgram(program);
		api->UseUniformBuffer(vertexBlock, 0);
		api->UseUniformBuffer(fragmentBlock, 1);
	}

	void TestEffect::SetTexSampler(TextureHandler texture)
	{
		api->UseTexture(texture, TEX_SAMPLER_TEX_UNIT, texSampler);
	}
}