#pragma once
#include "Maths/Maths.h"

namespace Ablaze
{

	struct Color
	{
		float r, g, b, a;

		Color(int r, int g, int b, int a = 255);
		Color(int color);
		Color();

		float GetBrightness() const;
		maths::vec4 rgba() const;
		maths::vec4 abgr() const;
		maths::vec4 bgra() const;
		maths::vec3 rgb() const;
		maths::vec3 bgr() const;
		maths::vec2 rg() const;
		maths::vec2 gb() const;
		maths::vec2 rb() const;

		float* ToFloat() const;
		float* ToVertexBuffer(const long long& vertexCount) const;

		static Color FromFloats(float r, float g, float b, float a = 1.0f);

		static Color White();
		static Color Black();

		static Color Red();
		static Color Green();
		static Color Blue();
	
		static Color Yellow();
		static Color Cyan();
		static Color Magenta();
	};

}