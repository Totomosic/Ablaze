#include "CollisionInfo.h"

namespace Ablaze
{

	CollisionInfo::CollisionInfo(bool collided, const maths::vec3& position, bool x, bool y, bool z)
		: collided(collided), position(position), x(x), y(y), z(z)
	{
	
	}

}