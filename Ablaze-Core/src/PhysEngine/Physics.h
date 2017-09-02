#pragma once
#include "stucts/AABB.h"
#include "stucts/OBB.h"
#include "stucts/CollisionInfo.h"
#include "stucts/RayCastInfo.h"
#include "Entities/GameObject.h"

namespace Ablaze
{

	class Physics
	{
	private:

	public:
		Physics() = delete;

		static CollisionInfo Contains(const AABB& boundingBox, const maths::vec3& boxPosition, const maths::vec3& point);
		static CollisionInfo Contains(const AABB& container, const maths::vec3& containerPosition, const AABB& object, const maths::vec3& objectPosition);
		static CollisionInfo Contains(const OBB& boundingBox, const maths::vec3& boxPosition, const maths::vec3& point);
		static CollisionInfo Intersects(const AABB& boundingBox, const maths::vec3& boxPosition, const AABB& other, const maths::vec3& otherPosition);
		static CollisionInfo Intersects(const OBB& boundingBox, const maths::vec3& boxPosition, const OBB& other, const maths::vec3& otherPosition);

		static RayCastInfo Raycast(const Ray& ray, const AABB& boundingBox, const maths::vec3& boxPosition);
		static RayCastInfo Raycast(const Ray& ray);

	private:
		static void SATTest(const maths::vec3& axis, maths::vec3* pointSet, const maths::vec3& positionOffset, float& minAlong, float& maxAlong);
		static bool OBBIntersects(const OBB& shape1, const maths::vec3& position1, const OBB& shape2, const maths::vec3& position2);
		static bool Overlaps(float min1, float max1, float min2, float max2);
		static inline bool IsBetween(float value, float low, float high);

	};

}