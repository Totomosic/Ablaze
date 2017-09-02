#include "Plane.h"

namespace Ablaze
{
	namespace maths
	{

		Plane::Plane(const maths::vec3& normal, float height)
			: normal(normal), height(height)
		{
		
		}

		Plane::Plane(float x, float y, float z, float height) : Plane(maths::vec3(x, y, z), height)
		{
			
		}

		Plane::Plane() : Plane(0, 1, 0, 0)
		{
		
		}

	}
}