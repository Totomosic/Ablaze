#pragma once
#include "Scene\Physics\stucts\BoundingBox.h"
#include "Scene\Physics\stucts\CollisionInfo.h"
#include "Scene\Physics\stucts\RayCastInfo.h"
#include "Entities\GameObject.h"

namespace Ablaze
{

	class Physics
	{
	private:

	public:
		Physics() { }

		static CollisionInfo Contains(const BoundingBox& boundingBox, const maths::vec3& boxPosition, const maths::vec3& point);
		static CollisionInfo Contains(const BoundingBox& container, const maths::vec3& containerPosition, const BoundingBox& object, const maths::vec3& objectPosition);
		static CollisionInfo Intersects(const BoundingBox& boundingBox, const maths::vec3& boxPosition, const BoundingBox& other, const maths::vec3& otherPosition);

		static RayCastInfo Raycast(const Ray& ray, const BoundingBox& boundingBox, const maths::vec3& boxPosition);
		static RayCastInfo Raycast(const Ray& ray);

	private:

	};

}