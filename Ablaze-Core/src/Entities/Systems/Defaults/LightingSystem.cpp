#include "LightingSystem.h"

namespace Ablaze
{

	LightingSystem::LightingSystem() : System()
	{

	}

	void LightingSystem::Run()
	{
		std::vector<GameObject*> gameObjects = GameObjects::GetAllWith<Components::Transform, Components::Light>();
		int lightCount = gameObjects.size();
		for (GameObject* obj : gameObjects)
		{
			Components::Transform* transform = obj->Transform();
			Components::Light* light = obj->GetComponent<Components::Light>();
		}
	}

}