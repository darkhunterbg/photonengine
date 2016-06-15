#include <photon\Services\Scene.h>
#include <photon\Services\AssetsService.h>

#include <photon\Math\Matrix.h>

class TestScene : public photon::Scene
{
	virtual void Initialize() override
	{
		//photon::TextureAsset& texture = photon::gl_AssetsService->GetTextureAsset("texture.dds");
		//photon::TextureAsset& texture = photon::gl_AssetsService->GetTextureAsset("texture.bmp");
	}

	virtual void Update() override
	{
		int texture = photon::gl_AssetsService->GetTextureAsset("texture.dds").textureID;
		int texture2 = photon::gl_AssetsService->GetTextureAsset("texture2.dds").textureID;

		for (int i = 0; i < 10; ++i)
		{
			photon::Matrix m = photon::Matrix::Translation({ (float)i - 5.0f,0.0f }) * photon::Matrix::Scale({ 0.5f,0.5f, 1 });
			photon::gl_GraphicsService->RenderObject(m, texture);

			m = photon::Matrix::Translation({ (float)i - 5.0f,1.0f }) * photon::Matrix::Scale({ 0.5f,0.5f, 1 });
			photon::gl_GraphicsService->RenderObject(m, texture2);
		}
	}
};