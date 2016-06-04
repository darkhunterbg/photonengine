#pragma once

#include "../Macro.h"
#include "MemoryStack.h"

namespace photon
{
	class Scene;

	class EXPORT SceneService
	{
		DISABLE_COPY(SceneService);

	private:
		static const int SCENE_STACK_SIZE = 16;

		int sceneIndex = -1;
		Scene* sceneStack[SCENE_STACK_SIZE];
		
		SceneService();
		~SceneService();

	public:
		static SceneService* Initialize( MemoryStack& stack);
		static void Uninitialize();
		
		Scene* GetCurrentScene() const;
		void PushScene(Scene* scene);
		void Update();
	};

	EXPORT extern SceneService* gl_SceneService;
}