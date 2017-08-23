#include "Font.h"
#include "Log.h"
#include "Utils/Virtual File System/VFS.h"

namespace Ablaze
{

	Font::Font(const String& name, String filename, float size) : Texture(name, VFS::ResolvePhysicalPath(filename), GL_TEXTURE_2D),
		size(size)
	{
		Create();
	}

	Font::~Font()
	{
		delete FTAtlas;
		delete FTFont;
	}

	float Font::GetSize() const
	{
		return size;
	}

	float Font::GetWidth(const String& text) const
	{
		float totalLength = 0;
		for (int i = 0; i < text.length(); i++)
		{
			char c = text[i];
			texture_glyph_t* glyph = texture_font_get_glyph(FTFont, c);
			if (glyph != nullptr)
			{
				if (i > 0)
				{
					float kerning = texture_glyph_get_kerning(glyph, text[i - 1]);
					totalLength += kerning;
				}
				totalLength += glyph->advance_x;
			}
		}
		return totalLength;
	}

	float Font::GetHeight(const String& text) const
	{
		float maxHeight = 0;
		for (int i = 0; i < text.length(); i++)
		{
			char c = text[i];
			texture_glyph_t* glyph = texture_font_get_glyph(FTFont, c);
			if (glyph != nullptr)
			{
				maxHeight = (glyph->height > maxHeight) ? glyph->height : maxHeight;
			}
		}
		return maxHeight;
	}

	maths::vec2 Font::GetSize(const String& text) const
	{
		return maths::vec2(GetWidth(text), GetHeight(text));
	}

	Model* Font::CreateModel(const String& modelName, const String& text, const Color& color) const
	{
		VertexBuffer* vbo = new VertexBuffer(text.length() * 4 * sizeof(Vertex), BufferLayout::Vertex());
		IndexBuffer* ibo = new IndexBuffer(text.length() * 6 * sizeof(GLuint));
		Vertex* buffer = (Vertex*)vbo->MapBuffer(Access::Write);
		GLuint* indices = new GLuint[text.length() * 6];
		float width = GetWidth(text);
		float height = GetHeight(text);
		float x = width / -2.0f;
		float y = height / -2.0f;
		int indexCount = 0;
		int indicesCount = 0;
		for (int i = 0; i < text.length(); i++)
		{
			char c = text[i];
			texture_glyph_t* glyph = texture_font_get_glyph(FTFont, c);
			if (glyph != nullptr)
			{
				if (i > 0)
				{
					float kerning = texture_glyph_get_kerning(glyph, text[i - 1]);
					x += kerning;
				}

				float x0 = x + glyph->offset_x;
				float y0 = y + glyph->offset_y;
				float x1 = x0 + glyph->width;
				float y1 = y0 - glyph->height;

				float u0 = glyph->s0;
				float v0 = glyph->t0;
				float u1 = glyph->s1;
				float v1 = glyph->t1;

				buffer->position = maths::vec3(x0, y0, 0);
				buffer->normal = maths::vec3(0, 0, 1);
				buffer->texCoord = maths::vec2(u0, v0);
				buffer->color = color;
				buffer++;

				buffer->position = maths::vec3(x0, y1, 0);
				buffer->normal = maths::vec3(0, 0, 1);
				buffer->texCoord = maths::vec2(u0, v1);
				buffer->color = color;
				buffer++;

				buffer->position = maths::vec3(x1, y1, 0);
				buffer->normal = maths::vec3(0, 0, 1);
				buffer->texCoord = maths::vec2(u1, v1);
				buffer->color = color;
				buffer++;

				buffer->position = maths::vec3(x1, y0, 0);
				buffer->normal = maths::vec3(0, 0, 1);
				buffer->texCoord = maths::vec2(u1, v0);
				buffer->color = color;
				buffer++;

				x += glyph->advance_x;
				y += glyph->advance_y;

				indices[indexCount + 0] = 0 + indicesCount;
				indices[indexCount + 1] = 1 + indicesCount;
				indices[indexCount + 2] = 2 + indicesCount;
				indices[indexCount + 3] = 0 + indicesCount;
				indices[indexCount + 4] = 2 + indicesCount;
				indices[indexCount + 5] = 3 + indicesCount;

				indexCount += 6;
				indicesCount += 4;
			}
			else
			{
				AB_WARN(String("Character not found: ") + c);
			}
		}
		vbo->UnmapBuffer();
		ibo->Bind();
		ibo->Upload(indices, text.length() * 6 * sizeof(GLuint));
		return new Model(modelName, vbo, ibo, maths::vec3(width, height, 0));
	}

	void Font::Create()
	{
		FTAtlas = texture_atlas_new(512, 512, 1);
		FTFont = texture_font_new_from_file(FTAtlas, size, path.c_str());
		glGenTextures(1, &FTAtlas->id);
		id = FTAtlas->id;
	}

}