#pragma once
#define _USE_MATH_DEFINES
#include <math.h>
// Includes all vectors along with mat4
#include "mat4.h"
#include "Ray.h"

namespace Ablaze
{
	namespace maths
	{
		class Angles
		{
		public:
			static float ToRadians(float degrees)
			{
				return degrees * ((float)M_PI / 180.0f);
			}

			static float ToDegrees(float radians)
			{
				return radians / (float)M_PI * 180.0f;
			}
		};
	}
}