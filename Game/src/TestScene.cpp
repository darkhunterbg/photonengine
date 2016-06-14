#include <photon\Services\Scene.h>
#include <photon\Services\AssetsService.h>

#include <photon\Math\Matrix.h>

class TestScene : public photon::Scene
{
	virtual void Initialize() override
	{
		photon::TextureAsset& texture = photon::gl_AssetsService->GetTextureAsset("texture.dds");
		//photon::TextureAsset& texture = photon::gl_AssetsService->GetTextureAsset("texture.bmp");
	}

	virtual void Update() override
	{
		for (int i = 0; i < 10; ++i)
		{
			photon::Matrix m = photon::Matrix::Translation({ (float) i -5,0.0f,0.0f });
			photon::gl_GraphicsService->RenderObject(m);
		}
	}
};