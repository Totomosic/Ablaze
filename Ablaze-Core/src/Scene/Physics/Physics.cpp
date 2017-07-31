#include "Physics.h"
#include "Log.h"

namespace Ablaze
{

	CollisionInfo Physics::Contains(const BoundingBox& boundingBox, const maths::vec3& boxPosition, const maths::vec3& point)
	{
		bool x = false, y = false, z = false;
		float w = boundingBox.GetSize().x / 2.0f, h = boundingBox.GetSize().y / 2.0f, d = boundingBox.GetSize().z / 2.0f;
		if (point.x > boxPosition.x - w && point.x < boxPosition.x + w)
		{
			x = true;
		}
		if (point.y > boxPosition.y - h && point.y < boxPosition.y + h)
		{
			y = true;
		}
		if (point.z > boxPosition.z - d && point.z < boxPosition.z + d)
		{
			z = true;
		}
		return CollisionInfo(x && y && z, point, x, y, z);
	}

	CollisionInfo Physics::Contains(const BoundingBox& container, const maths::vec3& containerPosition, const BoundingBox& object, const maths::vec3& objectPosition)
	{
		bool x = false, y = false, z = false;
		float w1 = container.GetSize().x / 2.0f, h1 = container.GetSize().y / 2.0f, d1 = container.GetSize().z / 2.0f;
		float w2 = object.GetSize().x / 2.0f, h2 = object.GetSize().y / 2.0f, d2 = object.GetSize().z / 2.0f;
		if (objectPosition.x - w2 > containerPosition.x - w1 && objectPosition.x + w2 < containerPosition.x + w1)
		{
			x = true;
		}
		if (objectPosition.y - h2 > containerPosition.y - h1 && objectPosition.y + h2 < containerPosition.y + h1)
		{
			y = true;
		}
		if (objectPosition.z - d2 > containerPosition.z - d1 && objectPosition.z + d2 < containerPosition.z + d1)
		{
			z = true;
		}
		return CollisionInfo(x && y && z, containerPosition, x, y, z);
	}

	CollisionInfo Physics::Intersects(const BoundingBox& boundingBox, const maths::vec3& boxPosition, const BoundingBox& object, const maths::vec3& objectPosition)
	{
		float w1 = boundingBox.GetSize().x / 2.0f;
		float h1 = boundingBox.GetSize().y / 2.0f;
		float d1 = boundingBox.GetSize().z / 2.0f;
		float w2 = object.GetSize().x / 2.0f;
		float h2 = object.GetSize().y / 2.0f;
		float d2 = object.GetSize().z / 2.0f;
		bool x = ((objectPosition.x - w2 > boxPosition.x - w1 && objectPosition.x - w2 < boxPosition.x + w1) || (objectPosition.x + w2 > boxPosition.x - w1 && objectPosition.x + w2 < boxPosition.x + w1) || (objectPosition.x - w2 < boxPosition.x - w1 && objectPosition.x + w2 > boxPosition.x + w1));
		bool y = ((objectPosition.y - h2 > boxPosition.y - h1 && objectPosition.y - h2 < boxPosition.y + h1) || (objectPosition.y + h2 > boxPosition.y - h1 && objectPosition.y + h2 < boxPosition.y + h1) || (objectPosition.y - h2 < boxPosition.y - h1 && objectPosition.y + h2 > boxPosition.y + h1));
		bool z = ((objectPosition.z - d2 > boxPosition.z - d1 && objectPosition.z - d2 < boxPosition.z + d1) || (objectPosition.z + d2 > boxPosition.z - d1 && objectPosition.z + d2 < boxPosition.z + d1) || (objectPosition.z - d2 < boxPosition.z - d1 && objectPosition.z + d2 > boxPosition.z + d1));
		return CollisionInfo(x && y && z, maths::vec3(0, 0, 0), x, y, z);
	}

	RayCastInfo Physics::Raycast(const Ray& ray, const BoundingBox& boundingBox, const maths::vec3& boxPosition)
	{
		return RayCastInfo();
	}

}