#pragma once
#include "vec4.h"

// Transformation happen from RIGHT TO LEFT
// Example:
// mat4::translation(vec3(5, 5, 5)) * mat4::rotation(M_PI / 4.0f, vec3(0, 0, 1));
// Rotates by 45 degrees around the z-axis then translates to position (5, 5, 5)

namespace Ablaze
{
	namespace maths
	{
		struct mat4
		{
			union
			{
				float values[4 * 4];
				vec4 columns[4];
			};

			mat4();
			mat4(float diagonal);
			mat4(float values[16]);

			vec4 GetColumn(int col) const;
			vec4 GetRow(int row) const;

			mat4 Multiply(const mat4& other) const;
			vec4 Multiply(const vec4& other) const;
			vec3 Multiply(const vec3& other) const;
			mat4 Inverse() const;

			static mat4 Identity();
			static mat4 Orthographic(float left, float right, float bottom, float top, float near, float far);
			static mat4 Perspective(float fov, float aspect, float near, float far);

			static mat4 Translation(const vec3& translation);
			static mat4 Translation(float x, float y, float z);
			static mat4 Rotation(double angle, const vec3& axis);
			static mat4 Scale(const vec3& scale);
			static mat4 Scale(float scale);

			friend mat4 operator*(const mat4& left, const mat4& right);
			friend vec4 operator*(const mat4& left, const vec4& right);
			friend vec3 operator*(const mat4& left, const vec3& right);
			mat4 operator*=(const mat4& right);

			friend std::ostream& operator<<(std::ostream& stream, const mat4& matrix);

		};
	}
}