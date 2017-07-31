#include "Vertex.h"

namespace Ablaze
{

	Vertex::Vertex(const maths::vec3& position, const maths::vec3& normal, const maths::vec2& texCoord, const Color& color, const maths::vec3& tangent)
	{
		this->position = position;
		this->normal = normal;
		this->texCoord = texCoord;
		this->color = color;
		this->tangent = tangent;
	}

}