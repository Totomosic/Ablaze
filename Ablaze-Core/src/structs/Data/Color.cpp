#include "Color.h"

namespace Ablaze
{

	Color::Color(int r, int g, int b, int a)
	{
		this->r = r / 255.0f;
		this->g = g / 255.0f;
		this->b = b / 255.0f;
		this->a = a / 255.0f;
	}

	Color::Color(int color) : Color(color, color, color, color)
	{

	}

	Color::Color() : Color(255)
	{

	}

	float Color::GetBrightness() const
	{
		return (r + b + g) / 3.0f;
	}

	maths::vec4 Color::rgba() const
	{
		return maths::vec4(r, g, b, a);
	}

	maths::vec4 Color::abgr() const
	{
		return maths::vec4(a, b, g, r);
	}

	maths::vec4 Color::bgra() const
	{
		return maths::vec4(b, g, r, a);
	}

	maths::vec3 Color::rgb() const
	{
		return maths::vec3(r, g, b);
	}

	maths::vec3 Color::bgr() const
	{
		return maths::vec3(b, g, r);
	}

	maths::vec2 Color::rg() const
	{
		return maths::vec2(r, g);
	}

	maths::vec2 Color::gb() const
	{
		return maths::vec2(g, b);
	}

	maths::vec2 Color::rb() const
	{
		return maths::vec2(r, b);
	}

	float* Color::ToFloat() const
	{
		return new float[4]{ r, g, b, a };
	}

	float* Color::ToVertexBuffer(const long long& vertexCount) const
	{
		float* values = new float[4 * vertexCount];
		float* color = ToFloat();

		for (int i = 0; i < vertexCount; i++)
		{
			values[i * 4 + 0] = color[0];
			values[i * 4 + 1] = color[1];
			values[i * 4 + 2] = color[2];
			values[i * 4 + 3] = color[3];
		}

		delete[] color;
		return values;
	}

	Color Color::FromFloats(float r, float g, float b, float a)
	{
		Color c((int)(r * 255), (int)(g * 255), (int)(b * 255), (int)(a * 255));
		return c;
	}

	Color Color::White()
	{
		Color c(255, 255, 255, 255);
		return c;
	}

	Color Color::Black()
	{
		Color c(0, 0, 0, 255);
		return c;
	}

	Color Color::Red()
	{
		Color c(255, 0, 0, 255);
		return c;
	}

	Color Color::Green()
	{
		Color c(0, 255, 0, 255);
		return c;
	}

	Color Color::Blue()
	{
		Color c(0, 0, 255, 255);
		return c;
	}

	Color Color::Yellow()
	{
		Color c(255, 255, 0, 255);
		return c;
	}

	Color Color::Cyan()
	{
		Color c(0, 255, 255, 255);
		return c;
	}

	Color Color::Magenta()
	{
		Color c(255, 0, 255, 255);
		return c;
	}

}