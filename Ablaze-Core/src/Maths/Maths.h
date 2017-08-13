#pragma once
#define _USE_MATH_DEFINES
#include <math.h>
// Includes all vectors along with mat4
#include "mat4.h"
#include "Ray.h"
#include "Random.h"

namespace Ablaze
{
	namespace maths
	{
		const double PI = M_PI;

		float Clamp(float value, float min, float max);
		float Map(float value, float min, float max, float newMin, float newMax);

		float ToRadians(float degrees);
		float ToDegrees(float radians);

	}
}