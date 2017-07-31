#include "vec4.h"

namespace Ablaze
{
	namespace maths
	{
		vec4::vec4(float x, float y, float z, float w)
		{
			this->x = x;
			this->y = y;
			this->z = z;
			this->w = w;
		}

		vec4::vec4(const vec3& vector, float w) : vec4::vec4(vector.x, vector.y, vector.z, w)
		{
		
			}

		vec4::vec4(const vec2& vector, float z, float w) : vec4::vec4(vector.x, vector.y, z, w)
		{

		}

		vec4::vec4(float xyz, float w) : vec4::vec4(xyz, xyz, xyz, w)
		{

		}

		vec4::vec4(float value) : vec4(value, value, value, value)
		{

		}

		float vec4::GetLengthSqrd() const
		{
			return x * x + y * y + z * z + w * w;
		}

		float vec4::GetLength() const
		{
			return sqrt(GetLengthSqrd());
		}

		float vec4::Dot(const vec4& other) const
		{
			return x * other.x + y * other.y + z * other.z + w * other.w;
		}

		vec4 vec4::Normalize() const
		{
			float length = GetLength();
			return vec4(x / length, y / length, z / length, w / length);
		}

		vec3 vec4::xyz() const
		{
			return vec3(x, y, z);
		}

		vec2 vec4::xy() const
		{
			return vec2(x, y);
		}

		vec4 vec4::Add(const vec4& other) const
		{
			return vec4(x + other.x, y + other.y, z + other.z, w + other.w);
		}

		vec4 vec4::Subtract(const vec4& other) const
		{
			return vec4(x - other.x, y - other.y, z - other.z, w - other.w);
		}

		vec4 vec4::Multiply(const vec4& other) const
		{
			return vec4(x * other.x, y * other.y, z * other.z, w - other.w);
		}

		vec4 vec4::Divide(const vec4& other) const
		{
			return vec4(x / other.x, y / other.y, z / other.z, w / other.w);
		}

		float vec4::Distance(const maths::vec4& a, const maths::vec4& b)
		{
			return (a - b).GetLength();
		}

		// operators

		vec4 operator+(const vec4& left, const vec4& right)
		{
			return left.Add(right);
		}

		vec4 operator-(const vec4& left, const vec4& right)
		{
			return left.Subtract(right);
		}

		vec4 operator*(const vec4& left, const vec4& right)
		{
			return left.Multiply(right);
		}

		vec4 operator/(const vec4& left, const vec4& right)
		{
			return left.Divide(right);
		}

		vec4 operator+(const vec4& left, float value)
		{
			return vec4(left.x + value, left.y + value, left.z + value, left.w + value);
		}

		vec4 operator-(const vec4& left, float value)
		{
			return vec4(left.x - value, left.y - value, left.z - value, left.w - value);
		}

		vec4 operator*(const vec4& left, float value)
		{
			return vec4(left.x * value, left.y * value, left.z * value, left.w * value);
		}

		vec4 operator/(const vec4& left, float value)
		{
			return vec4(left.x / value, left.y / value, left.z / value, left.w / value);
		}

		bool vec4::operator==(const vec4& other) const
		{
			return x == other.x && y == other.y && z == other.z && w == other.w;
		}

		bool vec4::operator!=(const vec4& other) const
		{
			return !(*this == other);
		}

		vec4 vec4::operator+=(const vec4& other)
		{
			*this = *this + other;
			return *this;
		}

		vec4 vec4::operator-=(const vec4& other)
		{
			*this = *this - other;
			return *this;
		}

		vec4 vec4::operator*=(const vec4& other)
		{
			*this = *this * other;
			return *this;
		}

		vec4 vec4::operator/=(const vec4& other)
		{
			*this = *this / other;
			return *this;
		}

		std::ostream& operator<<(std::ostream& stream, const vec4& vector)
		{
			stream << "vec4(" << vector.x << ", " << vector.y << ", " << vector.z << ", " << vector.w << ")";
			return stream;
		}
	}
}