#include "Cuboid.h"

namespace Ablaze
{

	Cuboid::Cuboid(const String& name, const maths::vec3& size, const Color& color) : Model(name, new VBO(24 * sizeof(Vertex), 0, 3, nullptr), new IndexBuffer(6 * 6 * sizeof(GLuint))),
		size(size)
	{
		Create(color);
	}

	const maths::vec3& Cuboid::GetSize() const
	{
		return size;
	}

	void Cuboid::Create(const Color& color)
	{
		//                                        Front                    Back                  Right                      Left                Top               Bottom
		indexBuffer->Upload(new GLuint[6 * 6]{ 0, 3, 6, 0, 6, 9,  12, 15, 18, 12, 18, 21,  11, 8, 17, 11, 17, 14,  23, 20, 5, 23, 5, 2,  22, 1, 10, 22, 10, 13,  4, 19, 16, 4, 16, 7 }, 6 * 6 * sizeof(GLuint));
		Vertex* ptr = (Vertex*)vbo->MapBuffer(GL_WRITE_ONLY);

		maths::vec3 s = size / 2.0f;
		maths::vec3 t(0, 0, 1);
		float x = s.x;
		float y = s.y;
		float z = s.z;

		// Front Top Left - Forward (0)
		ptr->position = maths::vec3(-x, y, z);
		ptr->normal = maths::vec3(0, 0, 1);
		ptr->texCoord = maths::vec2(0, 1);
		ptr->color = color;
		ptr->tangent = t;
		ptr++;

		// Front Top Left - Up (1)
		ptr->position = maths::vec3(-x, y, z);
		ptr->normal = maths::vec3(0, 1, 0);
		ptr->texCoord = maths::vec2(0, 0);
		ptr->color = color;
		ptr->tangent = t;
		ptr++;

		// Front Top Left - Left (2)
		ptr->position = maths::vec3(-x, y, z);
		ptr->normal = maths::vec3(-1, 0, 0);
		ptr->texCoord = maths::vec2(1, 1);
		ptr->color = color;
		ptr->tangent = t;
		ptr++;

		// Front Bottom Left - Forward (3)
		ptr->position = maths::vec3(-x, -y, z);
		ptr->normal = maths::vec3(0, 0, 1);
		ptr->texCoord = maths::vec2(0, 0);
		ptr->color = color;
		ptr->tangent = t;
		ptr++;

		// Front Bottom Left - Down (4)
		ptr->position = maths::vec3(-x, -y, z);
		ptr->normal = maths::vec3(0, -1, 0);
		ptr->texCoord = maths::vec2(0, 1);
		ptr->color = color;
		ptr->tangent = t;
		ptr++;

		// Front Bottom Left - Left (5)
		ptr->position = maths::vec3(-x, -y, z);
		ptr->normal = maths::vec3(-1, 0, 0);
		ptr->texCoord = maths::vec2(1, 0);
		ptr->color = color;
		ptr->tangent = t;
		ptr++;

		// Front Bottom Right - Forward (6)
		ptr->position = maths::vec3(x, -y, z);
		ptr->normal = maths::vec3(0, 0, 1);
		ptr->texCoord = maths::vec2(1, 0);
		ptr->color = color;
		ptr->tangent = t;
		ptr++;

		// Front Bottom Right - Down (7)
		ptr->position = maths::vec3(x, -y, z);
		ptr->normal = maths::vec3(0, -1, 0);
		ptr->texCoord = maths::vec2(1, 1);
		ptr->color = color;
		ptr->tangent = t;
		ptr++;

		// Front Bottom Right - Right (8)
		ptr->position = maths::vec3(x, -y, z);
		ptr->normal = maths::vec3(1, 0, 0);
		ptr->texCoord = maths::vec2(0, 0);
		ptr->color = color;
		ptr->tangent = t;
		ptr++;

		// Front Top Right - Forward (9)
		ptr->position = maths::vec3(x, y, z);
		ptr->normal = maths::vec3(0, 0, 1);
		ptr->texCoord = maths::vec2(1, 1);
		ptr->color = color;
		ptr->tangent = t;
		ptr++;

		// Front Top Right - Up (10)
		ptr->position = maths::vec3(x, y, z);
		ptr->normal = maths::vec3(0, 1, 0);
		ptr->texCoord = maths::vec2(1, 0);
		ptr->color = color;
		ptr->tangent = t;
		ptr++;

		// Front Top Right - Right (11)
		ptr->position = maths::vec3(x, y, z);
		ptr->normal = maths::vec3(1, 0, 0);
		ptr->texCoord = maths::vec2(0, 1);
		ptr->color = color;
		ptr->tangent = t;
		ptr++;

		// Back Top Right - Back (12)
		ptr->position = maths::vec3(x, y, -z);
		ptr->normal = maths::vec3(0, 0, -1);
		ptr->texCoord = maths::vec2(0, 1);
		ptr->color = color;
		ptr->tangent = t;
		ptr++;

		// Back Top Right - Up (13)
		ptr->position = maths::vec3(x, y, -z);
		ptr->normal = maths::vec3(0, 1, 0);
		ptr->texCoord = maths::vec2(1, 1);
		ptr->color = color;
		ptr->tangent = t;
		ptr++;

		// Back Top Right - Right (14)
		ptr->position = maths::vec3(x, y, -z);
		ptr->normal = maths::vec3(1, 0, 0);
		ptr->texCoord = maths::vec2(1, 1);
		ptr->color = color;
		ptr++;

		// Back Bottom Right - Back (15)
		ptr->position = maths::vec3(x, -y, -z);
		ptr->normal = maths::vec3(0, 0, -1);
		ptr->texCoord = maths::vec2(0, 0);
		ptr->color = color;
		ptr->tangent = t;
		ptr++;

		// Back Bottom Right - Down (16)
		ptr->position = maths::vec3(x, -y, -z);
		ptr->normal = maths::vec3(0, -1, 0);
		ptr->texCoord = maths::vec2(1, 0);
		ptr->color = color;
		ptr++;

		// Back Bottom Right - Right (17)
		ptr->position = maths::vec3(x, -y, -z);
		ptr->normal = maths::vec3(1, 0, 0);
		ptr->texCoord = maths::vec2(1, 0);
		ptr->color = color;
		ptr->tangent = t;
		ptr++;

		// Back Bottom Left - Back (18)
		ptr->position = maths::vec3(-x, -y, -z);
		ptr->normal = maths::vec3(0, 0, -1);
		ptr->texCoord = maths::vec2(1, 0);
		ptr->color = color;
		ptr++;

		// Back Bottom Left - Down (19)
		ptr->position = maths::vec3(-x, -y, -z);
		ptr->normal = maths::vec3(0, -1, 0);
		ptr->texCoord = maths::vec2(0, 0);
		ptr->color = color;
		ptr->tangent = t;
		ptr++;

		// Back Bottom Left - Left (20)
		ptr->position = maths::vec3(-x, -y, -z);
		ptr->normal = maths::vec3(-1, 0, 0);
		ptr->texCoord = maths::vec2(0, 0);
		ptr->color = color;
		ptr++;

		// Back Top Left - Back (21)
		ptr->position = maths::vec3(-x, y, -z);
		ptr->normal = maths::vec3(0, 0, -1);
		ptr->texCoord = maths::vec2(1, 1);
		ptr->color = color;
		ptr->tangent = t;
		ptr++;

		// Back Top Left - Top (22)
		ptr->position = maths::vec3(-x, y, -z);
		ptr->normal = maths::vec3(0, 1, 0);
		ptr->texCoord = maths::vec2(0, 1);
		ptr->color = color;
		ptr->tangent = t;
		ptr++;

		// Back Top Left - Left (23)
		ptr->position = maths::vec3(-x, y, -z);
		ptr->normal = maths::vec3(-1, 0, 0);
		ptr->texCoord = maths::vec2(0, 1);
		ptr->color = color;
		ptr->tangent = t;
		ptr++;

		auto val = vbo->UnmapBuffer();
	}

}