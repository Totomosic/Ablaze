#pragma once
#include "Maths/vec3.h"

namespace Ablaze
{

	struct Ray
	{
		maths::vec3 origin;
		maths::vec3 direction;

		Ray(const maths::vec3& origin, const maths::vec3& direction);

		friend std::ostream& operator<<(std::ostream& stream, const Ray& ray);
	};

}