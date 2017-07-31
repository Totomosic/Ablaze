#pragma once
#include <iostream>

namespace Ablaze
{
	namespace maths
	{
		struct vec2
		{
			float x, y;

			vec2(float x, float y);
			vec2(float value);
			vec2();

			float GetX() const { return x; };
			float GetY() const { return y; };

			float GetLength() const;
			float GetLengthSqrd() const;
			vec2 Normalize() const;
			float Dot(const vec2& other) const;

			vec2 Add(const vec2& other) const;
			vec2 Subtract(const vec2& other) const;
			vec2 Multiply(const vec2& other) const;
			vec2 Divide(const vec2& other) const;

			static float Distance(const maths::vec2& a, const maths::vec2& b);

			friend vec2 operator+(const vec2& left, const vec2& right);
			friend vec2 operator-(const vec2& left, const vec2& right);
			friend vec2 operator*(const vec2& left, const vec2& right);
			friend vec2 operator/(const vec2& left, const vec2& right);
			friend vec2 operator+(const vec2& left, float value);
			friend vec2 operator-(const vec2& left, float value);
			friend vec2 operator*(const vec2& left, float value);
			friend vec2 operator/(const vec2& left, float value);

			bool operator==(const vec2& other) const;
			bool operator!=(const vec2& other) const;

			vec2 operator+=(const vec2& other);
			vec2 operator-=(const vec2& other);
			vec2 operator*=(const vec2& other);
			vec2 operator/=(const vec2& other);

			friend std::ostream& operator<<(std::ostream& stream, const vec2& vector);
		};
	}
}