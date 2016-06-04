#include "SceneService.h"
#include "Scene.h"
#include "../Alloc.h"

namespace photon
{
	SceneService* gl_SceneService = nullptr;

	SceneService::SceneService()
	{

	}
	SceneService::~SceneService()
	{

	}

	SceneService* SceneService::Initialize(MemoryStack& stack)
	{
		ASSERT(gl_SceneService == nullptr);

		gl_SceneService = MEM_NEW(stack, SceneService)();

		return gl_SceneService;
	}
	void SceneService::Uninitialize()
	{
		ASSERT(gl_SceneService);

		gl_SceneService->~SceneService();
		gl_SceneService = nullptr;
	}

	Scene* SceneService::GetCurrentScene() const
	{
		if (sceneIndex < 0)
			return nullptr;

		return sceneStack[sceneIndex];
	}
	void SceneService::PushScene(Scene* scene)
	{
		ASSERT(scene);
		ASSERT(sceneIndex < SCENE_STACK_SIZE - 1);

		scene->Initialize();
		sceneStack[++sceneIndex] = scene;
	}
	void SceneService::Update()
	{
		Scene* scene = GetCurrentScene();

		if (scene)
		{
			scene->Update();
		}
			
	}
}