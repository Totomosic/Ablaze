#include "SceneManager.h"

namespace Ablaze
{

	Scene* SceneManager::currentScene = nullptr;

	Scene* SceneManager::CurrentScene()
	{
		return currentScene;
	}

	void SceneManager::SetCurrentScene(Scene* scene)
	{
		currentScene = scene;
	}

}