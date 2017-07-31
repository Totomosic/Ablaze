#include "vec2.h"

namespace Ablaze
{
	namespace maths
	{
		vec2::vec2(float x, float y)
		{
			this->x = x;
			this->y = y;
		}

		vec2::vec2(float value) : vec2(value, value)
		{

		}

		vec2::vec2() : vec2(0.0f)
		{

		}

		float vec2::GetLengthSqrd() const
		{
			return x * x + y * y;
		}

		float vec2::GetLength() const
		{
			return sqrt(GetLengthSqrd());
		}

		float vec2::Dot(const vec2& other) const
		{
			return x * other.x + y * other.y;
		}

		vec2 vec2::Normalize() const
		{
			float length = GetLength();
			return vec2(x / length, y / length);
		}

		vec2 vec2::Add(const vec2& other) const
		{
			return vec2(x + other.x, y + other.y);
		}

		vec2 vec2::Subtract(const vec2& other) const
		{
			return vec2(x - other.x, y - other.y);
		}

		vec2 vec2::Multiply(const vec2& other) const
		{
			return vec2(x * other.x, y * other.y);
		}

		vec2 vec2::Divide(const vec2& other) const
		{
			return vec2(x / other.x, y / other.y);
		}

		float vec2::Distance(const maths::vec2& a, const maths::vec2& b)
		{
			return (a - b).GetLength();
		}

		// operators

		vec2 operator+(const vec2& left, const vec2& right)
		{
			return left.Add(right);
		}

		vec2 operator-(const vec2& left, const vec2& right)
		{
			return left.Subtract(right);
		}

		vec2 operator*(const vec2& left, const vec2& right)
		{
			return left.Multiply(right);
		}

		vec2 operator/(const vec2& left, const vec2& right)
		{
			return left.Divide(right);
		}

		vec2 operator+(const vec2& left, float value)
		{
			return vec2(left.x + value, left.y + value);
		}

		vec2 operator-(const vec2& left, float value)
		{
			return vec2(left.x - value, left.y - value);
		}

		vec2 operator*(const vec2& left, float value)
		{
			return vec2(left.x * value, left.y * value);
		}

		vec2 operator/(const vec2& left, float value)
		{
			return vec2(left.x / value, left.y / value);
		}

		bool vec2::operator==(const vec2& other) const
		{
			return x == other.x && y == other.y;
		}

		bool vec2::operator!=(const vec2& other) const
		{
			return !(*this == other);
		}

		vec2 vec2::operator+=(const vec2& other)
		{
			*this = *this + other;
			return *this;
		}

		vec2 vec2::operator-=(const vec2& other)
		{
			*this = *this - other;
			return *this;
		}

		vec2 vec2::operator*=(const vec2& other)
		{
			*this = *this * other;
			return *this;
		}

		vec2 vec2::operator/=(const vec2& other)
		{
			*this = *this / other;
			return *this;
		}

		std::ostream& operator<<(std::ostream& stream, const vec2& vector)
		{
			stream << "vec2(" << vector.x << ", " << vector.y << ")";
			return stream;
		}
	}
}