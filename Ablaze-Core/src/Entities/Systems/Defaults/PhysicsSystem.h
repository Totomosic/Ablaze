#pragma once
#include "PhysEngine/Physics.h"
#include "Entities/Systems/System.h"

namespace Ablaze
{

	class PhysicsSystem : public System
	{
	public:
		PhysicsSystem();

		void Run() override;

	private:
		void SortObjects(const std::vector<GameObject*>& objects, std::vector<GameObject*>* outStaticObjects, std::vector<GameObject*>* outDynamicObjects);
		CollisionInfo TestAllCollisions(const Components::Collider& collider1, const Components::Transform& transform1, const maths::vec3& obj1Position, const maths::vec3& frameVelocity, const Components::Collider& collider2, const Components::Transform& transform2, const maths::vec3& obj2Position);

	};

}