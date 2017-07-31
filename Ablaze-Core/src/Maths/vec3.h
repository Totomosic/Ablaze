#pragma once
#include "vec2.h"

namespace Ablaze
{
	namespace maths
	{
		struct vec3
		{
			float x, y, z;

			vec3(float x, float y, float z);
			vec3(const vec2& vector, float z);
			vec3(float value);
			vec3();

			float GetX() const { return x; };
			float GetY() const { return y; };
			float GetZ() const { return z; };

			float GetLength() const;
			float GetLengthSqrd() const;
			vec3 Normalize() const;
			float Dot(const vec3& other) const;

			vec2 xy() const;

			vec3 Add(const vec3& other) const;
			vec3 Subtract(const vec3& other) const;
			vec3 Multiply(const vec3& other) const;
			vec3 Divide(const vec3& other) const;

			static float Distance(const maths::vec3& a, const maths::vec3& b);

			friend vec3 operator+(const vec3& left, const vec3& right);
			friend vec3 operator-(const vec3& left, const vec3& right);
			friend vec3 operator*(const vec3& left, const vec3& right);
			friend vec3 operator/(const vec3& left, const vec3& right);
			friend vec3 operator+(const vec3& left, float value);
			friend vec3 operator-(const vec3& left, float value);
			friend vec3 operator*(const vec3& left, float value);
			friend vec3 operator/(const vec3& left, float value);

			bool operator==(const vec3& other) const;
			bool operator!=(const vec3& other) const;

			vec3 operator+=(const vec3& other);
			vec3 operator-=(const vec3& other);
			vec3 operator*=(const vec3& other);
			vec3 operator/=(const vec3& other);

			friend std::ostream& operator<<(std::ostream& stream, const vec3& vector);
		};
	}
}