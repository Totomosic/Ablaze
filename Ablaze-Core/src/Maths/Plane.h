#pragma once
#include "vec3.h"

namespace Ablaze
{
	namespace maths
	{

		struct Plane
		{
			maths::vec3 normal;
			float height;

			Plane();
			Plane(const maths::vec3& normal, float height);
			Plane(float x, float y, float z, float height);
		};

	}
}