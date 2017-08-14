#include "Physics.h"
#include "Log.h"

namespace Ablaze
{

	CollisionInfo Physics::Contains(const AABB& boundingBox, const maths::vec3& boxPosition, const maths::vec3& point)
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

	CollisionInfo Physics::Contains(const AABB& container, const maths::vec3& containerPosition, const AABB& object, const maths::vec3& objectPosition)
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

	CollisionInfo Physics::Intersects(const AABB& boundingBox, const maths::vec3& boxPosition, const AABB& object, const maths::vec3& objectPosition)
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

	CollisionInfo Physics::Intersects(const OBB& boundingBox, const maths::vec3& boxPosition, const OBB& other, const maths::vec3& otherPosition)
	{
		CollisionInfo info(false, boxPosition, false, false, false);
		info.collided = OBBIntersects(boundingBox, boxPosition, other, otherPosition);
		return info;
	}

	RayCastInfo Physics::Raycast(const Ray& ray, const AABB& boundingBox, const maths::vec3& boxPosition)
	{
		return RayCastInfo();
	}

	void Physics::SATTest(const maths::vec3& axis, maths::vec3* pointSet, const maths::vec3& positionOffset, float& minAlong, float& maxAlong)
	{
		minAlong = HUGE;
		maxAlong = -HUGE;
		for (int i = 0; i < 8; i++)
		{
			float dotVal = (pointSet[i] + positionOffset).Dot(axis);
			if (dotVal < minAlong)
			{
				minAlong = dotVal;
			}
			if (dotVal > maxAlong)
			{
				maxAlong = dotVal;
			}
		}
	}

	bool Physics::OBBIntersects(const OBB& shape1, const maths::vec3& position1, const OBB& shape2, const maths::vec3& position2)
	{
		// Get the normals for one of the shapes,
		maths::vec3* shape1Normals = shape1.GetNormals();
		maths::vec3* shape2Normals = shape2.GetNormals();
		maths::vec3* shape1Corners = shape1.GetCorners();
		maths::vec3* shape2Corners = shape2.GetCorners();
		for (int i = 0; i < 6; i++)
		{
			float shape1Min, shape1Max, shape2Min, shape2Max;
			SATTest(shape1Normals[i], shape1Corners, position1, shape1Min, shape1Max);
			SATTest(shape1Normals[i], shape2Corners, position2, shape2Min, shape2Max);
			if (!Overlaps(shape1Min, shape1Max, shape2Min, shape2Max))
			{
				delete shape1Normals;
				delete shape2Normals;
				delete shape1Corners;
				delete shape2Corners;
				return false; // NO INTERSECTION
			}
		}

		for (int i = 0; i < 6; i++)
		{
			float shape1Min, shape1Max, shape2Min, shape2Max;
			SATTest(shape2Normals[i], shape1Corners, position1, shape1Min, shape1Max);
			SATTest(shape2Normals[i], shape2Corners, position2, shape2Min, shape2Max);
			if (!Overlaps(shape1Min, shape1Max, shape2Min, shape2Max))
			{
				delete shape1Normals;
				delete shape2Normals;
				delete shape1Corners;
				delete shape2Corners;
				return false; // NO INTERSECTION
			}
		}

		// if overlap occurred in ALL AXES, then they do intersect
		delete shape1Normals;
		delete shape2Normals;
		delete shape1Corners;
		delete shape2Corners;
		return true;
	}

	bool Physics::Overlaps(float min1, float max1, float min2, float max2)
	{
		return IsBetween(min2, min1, max1) || IsBetween(min1, min2, max2);
	}

	bool Physics::IsBetween(float value, float low, float high)
	{
		return low <= value && value <= high;
	}

}