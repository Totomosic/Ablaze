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

		for (auto shader : ShaderManager::GetAllShaders())
		{
			shader->Enable();
			shader->SetUniform("lightCount", lightCount);
			int count = 0;
			for (GameObject* obj : gameObjects)
			{
				Components::Transform* transform = obj->Transform();
				Components::Light* light = obj->GetComponent<Components::Light>();
				shader->SetUniform("Lights[" + std::to_string(count) + "].Position", transform->GetPosition());
				shader->SetUniform("Lights[" + std::to_string(count) + "].Color", light->GetColor().rgb());
				count++;
			}
		}
	}

}