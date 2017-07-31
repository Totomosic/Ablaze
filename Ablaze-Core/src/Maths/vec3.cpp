#include "vec3.h"

namespace Ablaze 
{
	namespace maths
	{
		vec3::vec3(float x, float y, float z)
			: x(x), y(y), z(z)
		{

		}

		vec3::vec3(const vec2& vector, float z) : vec3::vec3(vector.x, vector.y, z)
		{

		}

		vec3::vec3(float value) : vec3(value, value, value)
		{

		}

		vec3::vec3() : vec3(0.0f)
		{

		}

		float vec3::GetLengthSqrd() const
		{
			return x * x + y * y + z * z;
		}

		float vec3::GetLength() const
		{
			return sqrt(GetLengthSqrd());
		}

		float vec3::Dot(const vec3& other) const
		{
			return x * other.x + y * other.y + z * other.z;
		}

		vec3 vec3::Normalize() const
		{
			float length = GetLength();
			return vec3(x / length, y / length, z / length);
		}

		vec2 vec3::xy() const
		{
			return vec2(x, y);
		}

		vec3 vec3::Add(const vec3& other) const
		{
			return vec3(x + other.x, y + other.y, z + other.z);
		}

		vec3 vec3::Subtract(const vec3& other) const
		{
			return vec3(x - other.x, y - other.y, z - other.z);
		}

		vec3 vec3::Multiply(const vec3& other) const
		{
			return vec3(x * other.x, y * other.y, z * other.z);
		}

		vec3 vec3::Divide(const vec3& other) const
		{
			return vec3(x / other.x, y / other.y, z / other.z);
		}

		float vec3::Distance(const maths::vec3& a, const maths::vec3& b)
		{
			return (a - b).GetLength();
		}

		// operators

		vec3 operator+(const vec3& left, const vec3& right)
		{
			return left.Add(right);
		}

		vec3 operator-(const vec3& left, const vec3& right)
		{
			return left.Subtract(right);
		}

		vec3 operator*(const vec3& left, const vec3& right)
		{
			return left.Multiply(right);
		}

		vec3 operator/(const vec3& left, const vec3& right)
		{
			return left.Divide(right);
		}

		vec3 operator+(const vec3& left, float value)
		{
			return vec3(left.x + value, left.y + value, left.z + value);
		}

		vec3 operator-(const vec3& left, float value)
		{
			return vec3(left.x - value, left.y - value, left.z - value);
		}

		vec3 operator*(const vec3& left, float value)
		{
			return vec3(left.x * value, left.y * value, left.z * value);
		}

		vec3 operator/(const vec3& left, float value)
		{
			return vec3(left.x / value, left.y / value, left.z / value);
		}

		bool vec3::operator==(const vec3& other) const
		{
			return x == other.x && y == other.y && z == other.z;
		}

		bool vec3::operator!=(const vec3& other) const
		{
			return !(*this == other);
		}

		vec3 vec3::operator+=(const vec3& other)
		{
			*this = *this + other;
			return *this;
		}

		vec3 vec3::operator-=(const vec3& other)
		{
			*this = *this - other;
			return *this;
		}

		vec3 vec3::operator*=(const vec3& other)
		{
			*this = *this * other;
			return *this;
		}

		vec3 vec3::operator/=(const vec3& other)
		{
			*this = *this / other;
			return *this;
		}

		std::ostream& operator<<(std::ostream& stream, const vec3& vector)
		{
			stream << "vec3(" << vector.x << ", " << vector.y << ", " << vector.z << ")";
			return stream;
		}
	}
}