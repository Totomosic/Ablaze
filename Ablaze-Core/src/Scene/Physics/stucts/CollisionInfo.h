#pragma once
#include "Maths\Maths.h"

namespace Ablaze
{

	struct CollisionInfo
	{
		bool collided;
		maths::vec3 position;
		bool x, y, z;

		CollisionInfo(bool collided, const maths::vec3& position, bool x, bool y, bool z);

	};

}