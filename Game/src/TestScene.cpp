#include <photon\Services\Scene.h>
#include <photon\Services\AssetsService.h>


class TestScene : public photon::Scene
{
	virtual void Initialize() override
	{
		photon::TextureAsset& texture = photon::gl_AssetsService->GetTextureAsset("texture.dds");
	}

	virtual void Update() override
	{

	}
};