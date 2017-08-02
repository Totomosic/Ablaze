#pragma once
#include "Types.h"
#include "Maths/Maths.h"

#define _GL_ERRORS

namespace Ablaze
{

	class GameObject;

	class AblazeEngine
	{

	public:
		static uint maxEntities;

		static void Init();
		static void Terminate();

	};

}