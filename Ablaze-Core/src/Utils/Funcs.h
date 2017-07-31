#pragma once
#include "Maths/Maths.h"
#include "Types.h"

namespace Ablaze
{

	class Utils
	{
	public:
		Utils() { }

		static bool IsEquivalent(float a, float b, double tolerance = 0.1);
		static bool IsEquivalent(const maths::vec2& a, const maths::vec2& b, double tolerance = 0.1);
		static bool IsEquivalent(const maths::vec3& a, const maths::vec3& b, double tolerance = 0.1);
		static bool IsEquivalent(const maths::vec4& a, const maths::vec4& b, double tolerance = 0.1);

		static std::vector<String> SplitString(const String& string, const String& delimeters);
	};

}