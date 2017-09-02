#pragma once
#include "Maths/Maths.h"
#include "Entities/GameObject.h"

namespace Ablaze
{

	struct RayCastInfo
	{
		bool hit;
		maths::vec3 point;
		float length;
		const GameObject* hitObject;

		RayCastInfo() { }
	};

}