#pragma once
#include "Scene.h"

namespace Ablaze
{

	class SceneManager
	{
	private:
		static Scene* currentScene;

	public:
		static Scene* CurrentScene();

		static void SetCurrentScene(Scene* scene);
	};

}