#pragma once

#include <photon\Services\Scene.h>

using namespace photon;

class TestScene : public Scene
{
	virtual void Initialize() override;
	virtual void Update() override;
};