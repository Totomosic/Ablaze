#include "Funcs.h"

namespace Ablaze
{

	bool Utils::IsEquivalent(float a, float b, double tolerance)
	{
		return abs(b - a) <= tolerance;
	}

	bool Utils::IsEquivalent(const maths::vec2& a, const maths::vec2& b, double tolerance)
	{
		maths::vec2 result = b - a;
		return abs(result.x) <= tolerance && abs(result.y) <= tolerance;
	}

	bool Utils::IsEquivalent(const maths::vec3& a, const maths::vec3& b, double tolerance)
	{
		maths::vec3 result = b - a;
		return abs(result.x) <= tolerance && abs(result.y) <= tolerance && abs(result.z) <= tolerance;
	}

	bool Utils::IsEquivalent(const maths::vec4& a, const maths::vec4& b, double tolerance)
	{
		maths::vec4 result = b - a;
		return abs(result.x) <= tolerance && abs(result.y) <= tolerance && abs(result.z) <= tolerance && abs(result.w) <= tolerance;
	}

	std::vector<String> Utils::SplitString(const String& string, const String& delimiters)
	{
		size_t start = 0;
		size_t end = string.find_first_of(delimiters);

		std::vector<String> result;

		while (end <= String::npos)
		{
			String token = string.substr(start, end - start);
			if (!token.empty())
				result.push_back(token);

			if (end == String::npos)
				break;

			start = end + 1;
			end = string.find_first_of(delimiters, start);
		}

		return result;
	}

}