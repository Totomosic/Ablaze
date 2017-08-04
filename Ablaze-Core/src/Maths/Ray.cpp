#include "Ray.h"

namespace Ablaze
{

	Ray::Ray(const maths::vec3& origin, const maths::vec3& direction)
		: origin(origin), direction(direction)
	{
	
	}

	std::ostream& operator<<(std::ostream& stream, const Ray& ray)
	{
		stream << "Ray(orig: " << ray.origin << " dir: " << ray.direction << ")";
		return stream;
	}

}