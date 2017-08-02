#include "UpdateSystem.h"

namespace Ablaze
{

	UpdateSytem::UpdateSytem() : System()
	{
		
	}

	void UpdateSytem::Run()
	{
		std::vector<GameObject*> gameObjects = GameObjects::GetAllWith<Components::Transform, Components::RigidBody>();
		for (GameObject* obj : gameObjects)
		{
			Components::Transform* transform = obj->Transform();
			Components::RigidBody* rb = obj->GetComponent<Components::RigidBody>();

			rb->SetVelocity(rb->GetVelocity() + rb->GetAcceleration() * Time::DeltaTime());
			transform->Translate(rb->GetVelocity() * Time::DeltaTime(), Space::World);
			rb->SetAcceleration(maths::vec3(0.0));

			if (rb->AffectedByGravity())
			{
				rb->SetAcceleration(rb->GetAcceleration() + maths::vec3(0, -9.8f, 0));
			}
			rb->Velocity() *= maths::vec3(0.95f, 1.0f, 0.95f); // TODO: replace with proper friction
		}
	}

}