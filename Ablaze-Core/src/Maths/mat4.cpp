#include "mat4.h"
#include <iomanip>

namespace Ablaze
{
	namespace maths
	{
		mat4::mat4()
		{
			// instantiate every value to 0
			for (int i = 0; i < 4 * 4; i++)
			{
				values[i] = 0.0f;
			}
		}

		mat4::mat4(float vals[16])
		{
			for (int i = 0; i < 4 * 4; i++)
			{
				values[i] = vals[i];
			}
		}

		mat4::mat4(float diagonal) : mat4::mat4()
		{
			values[0 + 0 * 4] = diagonal;
			values[1 + 1 * 4] = diagonal;
			values[2 + 2 * 4] = diagonal;
			values[3 + 3 * 4] = diagonal;
		}

		vec4 mat4::GetColumn(int col) const
		{
			return maths::vec4(values[0 + col * 4], values[1 + col * 4], values[2 + col * 4], values[3 + col * 4]);
		}

		vec4 mat4::GetRow(int row) const
		{
			return maths::vec4(values[row + 0 * 4], values[row + 1 * 4], values[row + 2 * 4], values[row + 3 * 4]);
		}

		float mat4::GetElement(int row, int col) const
		{
			return values[row + col * 4];
		}

		mat4 mat4::Identity()
		{
			return mat4(1.0f);
		}

		mat4 mat4::Multiply(const mat4& other) const
		{
			float data[16];
			mat4 result;
			for (int y = 0; y < 4; y++)
			{
				for (int x = 0; x < 4; x++)
				{
					float sum = 0.0f;
					for (int e = 0; e < 4; e++)
					{
						sum += values[x + e * 4] * other.values[e + y * 4];
					}
					data[x + y * 4] = sum;
				}
			}
			memcpy(result.values, data, 16 * sizeof(float));
			return result;
		}

		vec4 mat4::Multiply(const vec4& other) const
		{
			return maths::vec4(values[0 + 0 * 4] * other.x + values[0 + 1 * 4] * other.y + values[0 + 2 * 4] * other.z + values[0 + 3 * 4] * other.w, values[1 + 0 * 4] * other.x + values[1 + 1 * 4] * other.y + values[1 + 2 * 4] * other.z + values[1 + 3 * 4] * other.w, values[2 + 0 * 4] * other.x + values[2 + 1 * 4] * other.y + values[2 + 2 * 4] * other.z + values[2 + 3 * 4] * other.w, values[3 + 0 * 4] * other.x + values[3 + 1 * 4] * other.y + values[3 + 2 * 4] * other.z + values[3 + 3 * 4] * other.w);
		}

		vec3 mat4::Multiply(const vec3& other) const
		{
			return Multiply(maths::vec4(other, 1)).xyz();
		}

		mat4 mat4::Inverse() const
		{
			double inv[16], det;
			float invOut[16];
			int i;

			inv[0] = values[5] * values[10] * values[15] -
				values[5] * values[11] * values[14] -
				values[9] * values[6] * values[15] +
				values[9] * values[7] * values[14] +
				values[13] * values[6] * values[11] -
				values[13] * values[7] * values[10];

			inv[4] = -values[4] * values[10] * values[15] +
				values[4] * values[11] * values[14] +
				values[8] * values[6] * values[15] -
				values[8] * values[7] * values[14] -
				values[12] * values[6] * values[11] +
				values[12] * values[7] * values[10];

			inv[8] = values[4] * values[9] * values[15] -
				values[4] * values[11] * values[13] -
				values[8] * values[5] * values[15] +
				values[8] * values[7] * values[13] +
				values[12] * values[5] * values[11] -
				values[12] * values[7] * values[9];

			inv[12] = -values[4] * values[9] * values[14] +
				values[4] * values[10] * values[13] +
				values[8] * values[5] * values[14] -
				values[8] * values[6] * values[13] -
				values[12] * values[5] * values[10] +
				values[12] * values[6] * values[9];

			inv[1] = -values[1] * values[10] * values[15] +
				values[1] * values[11] * values[14] +
				values[9] * values[2] * values[15] -
				values[9] * values[3] * values[14] -
				values[13] * values[2] * values[11] +
				values[13] * values[3] * values[10];

			inv[5] = values[0] * values[10] * values[15] -
				values[0] * values[11] * values[14] -
				values[8] * values[2] * values[15] +
				values[8] * values[3] * values[14] +
				values[12] * values[2] * values[11] -
				values[12] * values[3] * values[10];

			inv[9] = -values[0] * values[9] * values[15] +
				values[0] * values[11] * values[13] +
				values[8] * values[1] * values[15] -
				values[8] * values[3] * values[13] -
				values[12] * values[1] * values[11] +
				values[12] * values[3] * values[9];

			inv[13] = values[0] * values[9] * values[14] -
				values[0] * values[10] * values[13] -
				values[8] * values[1] * values[14] +
				values[8] * values[2] * values[13] +
				values[12] * values[1] * values[10] -
				values[12] * values[2] * values[9];

			inv[2] = values[1] * values[6] * values[15] -
				values[1] * values[7] * values[14] -
				values[5] * values[2] * values[15] +
				values[5] * values[3] * values[14] +
				values[13] * values[2] * values[7] -
				values[13] * values[3] * values[6];

			inv[6] = -values[0] * values[6] * values[15] +
				values[0] * values[7] * values[14] +
				values[4] * values[2] * values[15] -
				values[4] * values[3] * values[14] -
				values[12] * values[2] * values[7] +
				values[12] * values[3] * values[6];

			inv[10] = values[0] * values[5] * values[15] -
				values[0] * values[7] * values[13] -
				values[4] * values[1] * values[15] +
				values[4] * values[3] * values[13] +
				values[12] * values[1] * values[7] -
				values[12] * values[3] * values[5];

			inv[14] = -values[0] * values[5] * values[14] +
				values[0] * values[6] * values[13] +
				values[4] * values[1] * values[14] -
				values[4] * values[2] * values[13] -
				values[12] * values[1] * values[6] +
				values[12] * values[2] * values[5];

			inv[3] = -values[1] * values[6] * values[11] +
				values[1] * values[7] * values[10] +
				values[5] * values[2] * values[11] -
				values[5] * values[3] * values[10] -
				values[9] * values[2] * values[7] +
				values[9] * values[3] * values[6];

			inv[7] = values[0] * values[6] * values[11] -
				values[0] * values[7] * values[10] -
				values[4] * values[2] * values[11] +
				values[4] * values[3] * values[10] +
				values[8] * values[2] * values[7] -
				values[8] * values[3] * values[6];

			inv[11] = -values[0] * values[5] * values[11] +
				values[0] * values[7] * values[9] +
				values[4] * values[1] * values[11] -
				values[4] * values[3] * values[9] -
				values[8] * values[1] * values[7] +
				values[8] * values[3] * values[5];

			inv[15] = values[0] * values[5] * values[10] -
				values[0] * values[6] * values[9] -
				values[4] * values[1] * values[10] +
				values[4] * values[2] * values[9] +
				values[8] * values[1] * values[6] -
				values[8] * values[2] * values[5];

			det = values[0] * inv[0] + values[1] * inv[4] + values[2] * inv[8] + values[3] * inv[12];

			if (det == 0)
			{
				std::cout << "Matrix could not be inverted" << std::endl;
				return maths::mat4::Identity();
			}

			det = 1.0 / det;

			for (i = 0; i < 16; i++)
				invOut[i] = inv[i] * det;

			return mat4(invOut);
		}

		mat4 operator*(const mat4& left, const mat4& right)
		{
			return left.Multiply(right);
		}

		vec4 operator*(const mat4& left, const vec4& right)
		{
			return left.Multiply(right);
		}

		vec3 operator*(const mat4& left, const vec3& right)
		{
			return left.Multiply(right);
		}

		mat4 mat4::operator*=(const mat4& right)
		{
			*this = *this * right;
			return *this;
		}

		mat4 mat4::Orthographic(float left, float right, float bottom, float top, float near, float far)
		{
			mat4 result(1.0f);

			result.values[0 + 0 * 4] = 2.0f / (right - left);
			result.values[1 + 1 * 4] = 2.0f / (top - bottom);
			result.values[2 + 2 * 4] = -2.0f / (far - near);

			result.values[0 + 3 * 4] = -(left + right) / (right - left);
			result.values[1 + 3 * 4] = -(bottom + top) / (top - bottom);
			result.values[2 + 3 * 4] = -(far + near) / (far - near);

			return result;
		}

		mat4 mat4::Perspective(float fov, float aspect, float near, float far)
		{
			mat4 result(1.0f);

			float q = 1.0f / tan(0.5f * fov);
			float a = q / aspect;

			float b = (near + far) / (near - far);
			float c = (2.0f * near * far) / (near - far);

			result.values[0 + 0 * 4] = a;
			result.values[1 + 1 * 4] = q;
			result.values[2 + 2 * 4] = b;
			result.values[3 + 2 * 4] = -1.0f;
			result.values[2 + 3 * 4] = c;

			return result;
		}

		mat4 mat4::Translation(const vec3& translation)
		{
			mat4 result(1.0f);
			result.values[0 + 3 * 4] = translation.x;
			result.values[1 + 3 * 4] = translation.y;
			result.values[2 + 3 * 4] = translation.z;
			return result;
		}

		mat4 mat4::Translation(float x, float y, float z)
		{
			return Translation(maths::vec3(x, y, z));
		}

		mat4 mat4::Rotation(double angle, const vec3& axis)
		{
			mat4 result(1.0f);

			double c = cos(angle);
			double s = sin(angle);
			double omc = 1.0 - c;

			double x = axis.x;
			double y = axis.y;
			double z = axis.z;

			result.values[0 + 0 * 4] = x * omc + c;
			result.values[1 + 0 * 4] = y * x * omc + z * s;
			result.values[2 + 0 * 4] = x * z * omc - y * s;

			result.values[0 + 1 * 4] = x * y * omc - z * s;
			result.values[1 + 1 * 4] = y * omc + c;
			result.values[2 + 1 * 4] = y * z * omc + x * s;

			result.values[0 + 2 * 4] = x * z * omc + y * s;
			result.values[1 + 2 * 4] = y * z * omc - x * s;
			result.values[2 + 2 * 4] = z * omc + c;

			return result;
		}

		mat4 mat4::Scale(const vec3& scale)
		{
			mat4 result(1.0f);
			result.values[0 + 0 * 4] = scale.x;
			result.values[1 + 1 * 4] = scale.y;
			result.values[2 + 2 * 4] = scale.z;
			return result;
		}

		mat4 mat4::Scale(float x, float y, float z)
		{
			return Scale(maths::vec3(x, y, z));
		}

		mat4 mat4::Scale(float scale)
		{
			return mat4::Scale(maths::vec3(scale));
		}

		mat4 mat4::InvertX(const maths::mat4& other)
		{
			mat4 flipMatrix = Scale(-1.f, 1.f, 1.f);
			return flipMatrix * other * flipMatrix;
		}

		mat4 mat4::InvertY(const maths::mat4& other)
		{
			mat4 flipMatrix = Scale(1.f, -1.f, 1.f);
			return flipMatrix * other * flipMatrix;
		}

		mat4 mat4::InvertZ(const maths::mat4& other)
		{
			mat4 flipMatrix = Scale(1.f, 1.f, -1.f);
			return flipMatrix * other * flipMatrix;
		}

		std::ostream& operator<<(std::ostream& stream, const mat4& matrix)
		{
			const char* s = " ";
			stream << "|" << matrix.values[0 + 0 * 4] << s << matrix.values[0 + 1 * 4] << s << matrix.values[0 + 2 * 4] << s << matrix.values[0 + 3 * 4] << "|" << std::endl
				<< "|" << matrix.values[1 + 0 * 4] << s << matrix.values[1 + 1 * 4] << s << matrix.values[1 + 2 * 4] << s << matrix.values[1 + 3 * 4] << "|" << std::endl
				<< "|" << matrix.values[2 + 0 * 4] << s << matrix.values[2 + 1 * 4] << s << matrix.values[2 + 2 * 4] << s << matrix.values[2 + 3 * 4] << "|" << std::endl
				<< "|" << matrix.values[3 + 0 * 4] << s << matrix.values[3 + 1 * 4] << s << matrix.values[3 + 2 * 4] << s << matrix.values[3 + 3 * 4] << "|";
			return stream;
		}
	}
}