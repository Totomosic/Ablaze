#pragma once
#include "AblazeGL.h"
#include "Graphics/Imaging/ImageLoader.h"

namespace Ablaze
{

	class TextureFactory;
	class Framebuffer;
	class TextureManager;

	class Texture
	{
	protected:
		String name;
		String path;
		GLuint id;
		GLenum textureTarget;
		GLsizei width, height;
		GLint bindUnit;

	protected:
		Texture(const String& name, const String& filepath, GLenum target = GL_TEXTURE_2D);
		Texture(const String& name, GLenum target, int width, int height);

	public:
		virtual ~Texture();

		const GLuint GetID() const;
		const String& GetPath() const;
		const String& GetName() const;
		const GLint GetBindUnit() const;

		GLint Bind();
		GLint Unbind();

		void SetTextureParameter(GLenum parameter, GLint value) const;

		inline const uint GetWidth() const { return width; }
		inline const uint GetHeight() const { return height; }

		friend class TextureFactory;
		friend class Framebuffer;
		friend class TextureManager;

	protected:
		virtual void Create() = 0;
		void SetBindUnit(GLint unit);

	};

}