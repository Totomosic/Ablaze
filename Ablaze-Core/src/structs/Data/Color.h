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