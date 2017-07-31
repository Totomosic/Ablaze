#include "PhysicsSystem.h"
#include "Utils/Funcs.h"

namespace Ablaze
{

	PhysicsSystem::PhysicsSystem() : System()
	{
	
	}

	void PhysicsSystem::Run()
	{
		std::vector<GameObject*> gameObjects = GameObjects::GetAllWith<Components::Transform, Components::Collider, Components::RigidBody>();

		std::vector<GameObject*> staticObjects;
		std::vector<GameObject*> dynamicObjects;
		SortObjects(gameObjects, &staticObjects, &dynamicObjects);

		for (GameObject* dynamicObj : dynamicObjects)
		{
			Components::Transform* dynamicTransform = dynamicObj->Transform();
			Components::Collider* dynamicCollider = dynamicObj->GetComponent<Components::Collider>();
			Components::RigidBody* dynamicRb = dynamicObj->GetComponent<Components::RigidBody>();

			maths::vec3 dVelThisFrame = (dynamicRb->GetVelocity() + dynamicRb->GetAcceleration()) * Time::DeltaTime();

			for (GameObject* staticObj : staticObjects)
			{
				Components::Transform* staticTransform = staticObj->Transform();
				Components::Collider* staticCollider = staticObj->GetComponent<Components::Collider>();
				Components::RigidBody* staticRb = staticObj->GetComponent<Components::RigidBody>();
				CollisionInfo info = TestAllCollisions(*dynamicCollider, *dynamicTransform, dynamicTransform->GetPosition(), dVelThisFrame, *staticCollider, *staticTransform, staticTransform->GetPosition());
				if (info.x)
				{
					dynamicRb->Acceleration().x = 0;
					dynamicRb->Velocity().x = 0;
				}
				if (info.y)
				{
					dynamicRb->Acceleration().y = 0;
					dynamicRb->Velocity().y = 0;
				}
				if (info.z)
				{
					dynamicRb->Acceleration().z = 0;
					dynamicRb->Velocity().z = 0;
				}
			}
		}
	}

	void PhysicsSystem::SortObjects(const std::vector<GameObject*>& objects, std::vector<GameObject*>* outStaticObjects, std::vector<GameObject*>* outDynamicObjects)
	{
		for (GameObject* obj : objects)
		{
			if (obj->GetComponent<Components::RigidBody>()->IsStatic())
			{
				outStaticObjects->push_back(obj);
			}
			else
			{
				outDynamicObjects->push_back(obj);
			}
		}
	}
	
	CollisionInfo PhysicsSystem::TestAllCollisions(const Components::Collider& collider1, const Components::Transform& transform1, const maths::vec3& obj1Position, const maths::vec3& frameVelocity, const Components::Collider& collider2, const Components::Transform& transform2, const maths::vec3& obj2Position)
	{
		CollisionInfo info(false, maths::vec3(0.0f), false, false, false);
		for (int i = 0; i < collider1.GetCount(); i++)
		{
			BoundingBox bbox1 = collider1.GetBoundingBox(i);
			bbox1.size *= transform1.GetScale();
			maths::vec3 position1 = collider1.GetPositionOffset(i);
			for (int j = 0; j < collider2.GetCount(); j++)
			{
				BoundingBox bbox2 = collider2.GetBoundingBox(j);
				bbox2.size *= transform2.GetScale();
				maths::vec3 position2 = collider2.GetPositionOffset(j);
				CollisionInfo xCollision = Physics::Intersects(bbox2, obj2Position + position2, bbox1, obj1Position + position1 + maths::vec3(frameVelocity.x, 0, 0));
				CollisionInfo yCollision = Physics::Intersects(bbox2, obj2Position + position2, bbox1, obj1Position + position1 + maths::vec3(0, frameVelocity.y, 0));
				CollisionInfo zCollision = Physics::Intersects(bbox2, obj2Position + position2, bbox1, obj1Position + position1 + maths::vec3(0, 0, frameVelocity.z));

				info.x = xCollision.collided || info.x;
				info.y = yCollision.collided || info.y;
				info.z = zCollision.collided || info.z;
				info.collided = info.x || info.y || info.z;
			}
		}
		return info;
	}
}