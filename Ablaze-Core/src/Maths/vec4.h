#pragma once
#include "vec3.h"

namespace Ablaze
{
	namespace maths
	{
		struct vec4
		{
			float x, y, z, w;

			vec4(float x, float y, float z, float w);
			vec4(const vec3& vector, float w);
			vec4(const vec2& vector, float z, float w);
			vec4(float xyz, float w);
			vec4(float value);
			vec4() = default;

			float GetX() const { return x; };
			float GetY() const { return y; };
			float GetZ() const { return z; };
			float GetW() const { return w; };

			vec2 xy() const;
			vec3 xyz() const;

			float GetLength() const;
			float GetLengthSqrd() const;
			vec4 Normalize() const;
			float Dot(const vec4& other) const;

			vec4 Add(const vec4& other) const;
			vec4 Subtract(const vec4& other) const;
			vec4 Multiply(const vec4& other) const;
			vec4 Divide(const vec4& other) const;

			static float Distance(const maths::vec4& a, const maths::vec4& b);

			friend vec4 operator+(const vec4& left, const vec4& right);
			friend vec4 operator-(const vec4& left, const vec4& right);
			friend vec4 operator*(const vec4& left, const vec4& right);
			friend vec4 operator/(const vec4& left, const vec4& right);
			friend vec4 operator+(const vec4& left, float value);
			friend vec4 operator-(const vec4& left, float value);
			friend vec4 operator*(const vec4& left, float value);
			friend vec4 operator/(const vec4& left, float value);

			bool operator==(const vec4& other) const;
			bool operator!=(const vec4& other) const;

			vec4 operator+=(const vec4& other);
			vec4 operator-=(const vec4& other);
			vec4 operator*=(const vec4& other);
			vec4 operator/=(const vec4& other);

			friend std::ostream& operator<<(std::ostream& stream, const vec4& vector);
		};
	}
}