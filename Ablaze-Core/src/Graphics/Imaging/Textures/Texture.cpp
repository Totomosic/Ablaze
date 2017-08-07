#include "Texture.h"
#include "TextureManager.h"

namespace Ablaze
{

	Texture::Texture(const String& name, const String& filename, GLenum target)
		: name(name), path(filename), textureTarget(target), bindUnit(-1)
	{
		
	}

	Texture::Texture(const String& name, GLenum target, int width, int height)
		: name(name), textureTarget(target), width(width), height(height)
	{
		
	}

	Texture::~Texture()
	{
		glDeleteTextures(1, &id);
	}

	const GLuint Texture::GetID() const
	{
		return id;
	}

	const GLenum Texture::GetTarget() const
	{
		return textureTarget;
	}

	const String& Texture::GetPath() const
	{
		return path;
	}

	const String& Texture::GetName() const
	{
		return name;
	}

	const GLint Texture::GetBindUnit() const
	{
		return bindUnit;
	}

	GLint Texture::Bind()
	{
		TextureManager::Bind(this);
		return bindUnit;
	}

	GLint Texture::Unbind()
	{
		TextureManager::Unbind(this);
		return bindUnit;
	}

	void Texture::SetTextureParameter(GLenum parameter, GLint value) const
	{
		glTexParameteri(textureTarget, parameter, value);
	}

	void Texture::Create()
	{
		
	}

	void Texture::SetBindUnit(GLint unit)
	{
		bindUnit = unit;
	}

}