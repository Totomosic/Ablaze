#include "Rectangle.h"

namespace Ablaze
{

	Rectangle::Rectangle(const String& name, const maths::vec2& size, const Color& color) : Model(name, new VBO(4 * sizeof(Vertex), BufferLayout::Vertex()), new IndexBuffer(6 * sizeof(GLuint)), maths::vec3(size.x, size.y, 0))
	{
		Create(color);
	}

	void Rectangle::Create(const Color& color)
	{
		indexBuffer->Bind();
		indexBuffer->Upload(new GLuint[6]{ 0, 1, 2, 0, 2, 3 }, 6 * sizeof(GLuint));
		auto ptr = (Vertex*)vbo->MapBuffer(Access::Write);

		maths::vec3 n(0, 0, 1);
		maths::vec3 s = size / 2.0f;
		float x = s.x;
		float y = s.y;

		ptr->position = maths::vec3(-x, y, 0);
		ptr->normal = n;
		ptr->texCoord = maths::vec2(0, 0);
		ptr->color = color;
		ptr++;

		ptr->position = maths::vec3(-x, -y, 0);
		ptr->normal = n;
		ptr->texCoord = maths::vec2(0, 1);
		ptr->color = color;
		ptr++;

		ptr->position = maths::vec3(x, -y, 0);
		ptr->normal = n;
		ptr->texCoord = maths::vec2(1, 1);
		ptr->color = color;
		ptr++;

		ptr->position = maths::vec3(x, y, 0);
		ptr->normal = n;
		ptr->texCoord = maths::vec2(1, 0);
		ptr->color = color;

		auto val = vbo->UnmapBuffer();
	}

}