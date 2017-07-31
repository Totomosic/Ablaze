#include "Tile.h"

namespace Ablaze
{

	Tile::Tile(const String& name, const maths::vec2& size, const Color& color) : Model(name, new VBO(4 * sizeof(Vertex), 0), new IndexBuffer(6 * sizeof(GLuint)))
	{
		this->size = size;
		Create(color);
	}

	const maths::vec2& Tile::GetSize() const
	{
		return size;
	}

	void Tile::Create(const Color& color)
	{
		Vertex* ptr = (Vertex*)vbo->MapBuffer(GL_WRITE_ONLY);
		GLuint* indices = (GLuint*)indexBuffer->MapBuffer(GL_WRITE_ONLY);
		float w = size.x / 2.0f;
		float d = size.y / 2.0f;
		maths::vec3 normal(0.0f, 1.0f, 0.0f);

		ptr->position = maths::vec3(-w, 0.0f, -d);
		ptr->normal = normal;
		ptr->texCoord = maths::vec2(0.0f, 1.0f);
		ptr->color = color;
		ptr->tangent = maths::vec3(0, 0, -1); // TEST REQUIRED
		ptr++;

		ptr->position = maths::vec3(-w, 0.0f, d);
		ptr->normal = normal;
		ptr->texCoord = maths::vec2(0.0f, 0.0f);
		ptr->color = color;
		ptr->tangent = maths::vec3(0, 0, -1); // TEST REQUIRED
		ptr++;

		ptr->position = maths::vec3(w, 0.0f, d);
		ptr->normal = normal;
		ptr->texCoord = maths::vec2(1.0f, 0.0f);
		ptr->color = color;
		ptr->tangent = maths::vec3(0, 0, -1); // TEST REQUIRED
		ptr++;

		ptr->position = maths::vec3(w, 0.0f, -d);
		ptr->normal = normal;
		ptr->texCoord = maths::vec2(1.0f, 1.0f);
		ptr->color = color;
		ptr->tangent = maths::vec3(0, 0, -1); // TEST REQUIRED

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