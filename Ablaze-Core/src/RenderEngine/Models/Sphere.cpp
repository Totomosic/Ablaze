#include "Sphere.h"

namespace Ablaze
{

	Sphere::Sphere(const String& name, float radius, const Color& color) : Model(name, new VBO((4 * (180 / 10 + 1) * ((360 - 10) / 10 + 1)) * sizeof(Vertex), 0), new IndexBuffer((4 * (180 / 10 + 1) * ((360 - 10) / 10 + 1)) * sizeof(GLuint)), maths::vec3(radius * 2))
	{
		this->radius = radius;
		Create(color);
	}

	float Sphere::GetRadius() const
	{
		return radius;
	}

	void Sphere::Create(const Color& color)
	{
		float space = 10;
		Vertex* ptr = (Vertex*)vbo->MapBuffer(Access::Write);
		GLuint* indices = (GLuint*)indexBuffer->MapBuffer(Access::Write);
		uint currentVertex = 0;

		for (float b = 0; b <= 180; b += space)
		{
			for (float a = 0; a <= 360 - space; a += space)
			{
				maths::vec3 v0 = maths::vec3((float)(radius * sin(maths::Angles::ToRadians(a)) * sin(maths::Angles::ToRadians(b))), (float)(radius * cos(maths::Angles::ToRadians(a)) * sin(maths::Angles::ToRadians(b))), (float)(radius * cos(maths::Angles::ToRadians(b))));
				maths::vec2 tex0 = maths::vec2((b) / 360.0f, (a) / 360.0f);

				maths::vec3 v1 = maths::vec3((float)(radius * sin(maths::Angles::ToRadians(a)) * sin(maths::Angles::ToRadians(b - space))), (float)(radius * cos(maths::Angles::ToRadians(a)) * sin(maths::Angles::ToRadians(b - space))), (float)(radius * cos(maths::Angles::ToRadians(b - space))));
				maths::vec2 tex1 = maths::vec2((b - space) / 360.0f, (a) / 360.0f);

				maths::vec3 v2 = maths::vec3((float)(radius * sin(maths::Angles::ToRadians(a - space)) * sin(maths::Angles::ToRadians(b))), (float)(radius * cos(maths::Angles::ToRadians(a - space)) * sin(maths::Angles::ToRadians(b))), (float)(radius * cos(maths::Angles::ToRadians(b))));
				maths::vec2 tex2 = maths::vec2((b) / 360.0f, (a - space) / 360.0f);

				maths::vec3 v3 = maths::vec3((float)(radius * sin(maths::Angles::ToRadians(a - space)) * sin(maths::Angles::ToRadians(b - space))), (float)(radius * cos(maths::Angles::ToRadians(a - space)) * sin(maths::Angles::ToRadians(b - space))), (float)(radius * cos(maths::Angles::ToRadians(b - space))));
				maths::vec2 tex3 = maths::vec2((b - space) / 360.0f, (a - space) / 360.0f);

				maths::vec3 deltaPos1 = v1 - v0;
				maths::vec3 deltaPos2 = v2 - v0;
				maths::vec2 deltaUV1 = tex1 - tex0;
				maths::vec2 deltaUV2 = tex2 - tex0;
				float r = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV1.y * deltaUV2.x);
				maths::vec3 tangent1 = (deltaPos1 * deltaUV2.y - deltaPos2 * deltaUV1.y) * r;

				deltaPos1 = v2 - v1;
				deltaPos2 = v3 - v1;
				deltaUV1 = tex2 - tex1;
				deltaUV2 = tex3 - tex1;
				r = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV1.y * deltaUV2.x);
				maths::vec3 tangent2 = (deltaPos1 * deltaUV2.y - deltaPos2 * deltaUV1.y) * r;

				ptr->position = v0;
				ptr->normal = v0.Normalize();
				ptr->texCoord = tex0;
				ptr->color = color;
				ptr->tangent = tangent1;
				ptr++;

				ptr->position = v1;
				ptr->normal = v1.Normalize();
				ptr->texCoord = tex1;
				ptr->color = color;
				ptr->tangent = tangent1;
				ptr++;

				ptr->position = v2;
				ptr->normal = v2.Normalize();
				ptr->texCoord = tex2;
				ptr->color = color;
				ptr->tangent = tangent2;
				ptr++;

				ptr->position = v3;
				ptr->normal = v3.Normalize();
				ptr->texCoord = tex3;
				ptr->color = color;
				ptr->tangent = tangent2;
				ptr++;

				*indices = 0 + currentVertex;
				indices++;
				*indices = 1 + currentVertex;
				indices++;
				*indices = 2 + currentVertex;
				indices++;
				*indices = 3 + currentVertex;
				indices++;

				currentVertex += 4;
			}
		}
		vbo->UnmapBuffer();
		indexBuffer->UnmapBuffer();
		vao->SetPrimitiveType(GL_TRIANGLE_STRIP);
	}

}