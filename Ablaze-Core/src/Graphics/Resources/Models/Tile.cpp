#include "Tile.h"

namespace Ablaze
{

	Tile::Tile(const String& name, const maths::vec2& size, const Color& color) : Model(name, new VertexBuffer(4 * sizeof(Vertex), BufferLayout::Vertex()), new IndexBuffer(6 * sizeof(GLuint)), maths::vec3(size.x, 0, size.y))
	{
		Create(color);
	}

	void Tile::Create(const Color& color)
	{
		Vertex* ptr = (Vertex*)vbo->MapBuffer(Access::Write);
		GLuint* indices = (GLuint*)indexBuffer->MapBuffer(Access::Write);
		float w = size.x / 2.0f;
		float d = size.z / 2.0f;
		maths::vec3 normal(0.0f, 1.0f, 0.0f);

		ptr->position = maths::vec3(-w, 0.0f, -d);
		ptr->normal = normal;
		ptr->texCoord = maths::vec2(0.0f, 1.0f);
		ptr->color = color;
		ptr->tangent = maths::vec3(0, 0, 1); // TEST REQUIRED
		ptr++;

		ptr->position = maths::vec3(-w, 0.0f, d);
		ptr->normal = normal;
		ptr->texCoord = maths::vec2(0.0f, 0.0f);
		ptr->color = color;
		ptr->tangent = maths::vec3(0, 0, 1); // TEST REQUIRED
		ptr++;

		ptr->position = maths::vec3(w, 0.0f, d);
		ptr->normal = normal;
		ptr->texCoord = maths::vec2(1.0f, 0.0f);
		ptr->color = color;
		ptr->tangent = maths::vec3(0, 0, 1); // TEST REQUIRED
		ptr++;

		ptr->position = maths::vec3(w, 0.0f, -d);
		ptr->normal = normal;
		ptr->texCoord = maths::vec2(1.0f, 1.0f);
		ptr->color = color;
		ptr->tangent = maths::vec3(0, 0, 1); // TEST REQUIRED

		*indices = 0;
		indices++;
		*indices = 1;
		indices++;
		*indices = 2;
		indices++;
		*indices = 0;
		indices++;
		*indices = 2;
		indices++;
		*indices = 3;

		vbo->UnmapBuffer();
		indexBuffer->UnmapBuffer();
	}

}