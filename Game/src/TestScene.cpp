#include <photon\Services\Scene.h>
#include <photon\Services\AssetsService.h>


class TestScene : public photon::Scene
{
	virtual void Initialize() override
	{
		photon::TextAsset asset = photon::gl_AssetsService->GetTextAsset("test.txt");
		photon::gl_AssetsService->GetTextAsset("test.txt");
	}

	virtual void Update() override
	{

	}
};