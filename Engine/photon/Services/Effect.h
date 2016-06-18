#pragma once

#include "../Macro.h"
#include "../GraphicsAPI/GraphicsAPI.h"


namespace photon
{
	class GraphicsDevice;

	template <int T>
	class Effect
	{
		DISABLE_COPY(Effect<T>);

	protected:
		GraphicsAPI* api;

	public:
		static const int ID = T;

		Effect(GraphicsAPI* api) :
			api(api)
		{
		}
		~Effect() = default;
	};

	class TestEffect : public Effect<0>
	{
	private:
		UniformBufferHandler vertexBlock;
		UniformBufferHandler fragmentBlock;

		int texSampler;

		ShaderProgramHandler program;
	public:
		static const int TEX_SAMPLER_TEX_UNIT = 0;

		TestEffect(GraphicsAPI* api, GraphicsDevice* device);
		~TestEffect() = default;

		void UpdateVertexBlock( const Matrix& view , const Matrix& proj);
		void UpdateFragmentBlock( const Vector4& vector);
		void Bind();
		void SetTexSampler(TextureHandler texture);
	};
}