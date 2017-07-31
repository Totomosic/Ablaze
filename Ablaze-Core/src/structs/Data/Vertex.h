#pragma once
#include "AblazeGL.h"
#include "Maths/Maths.h"
#include "Color.h"

namespace Ablaze
{

	struct Vertex
	{
		maths::vec3 position;
		maths::vec3 normal;
		maths::vec2 texCoord;
		Color color;
		maths::vec3 tangent;

		Vertex(const maths::vec3& position, const maths::vec3& normal, const maths::vec2& texCoord, const Color& color, const maths::vec3& tangent);
	};

}