#include "Texture.h"
#include "TextureManager.h"

namespace Ablaze
{

	Texture::Texture(const String& name, const String& filename, GLenum target) : Asset(name), 
		path(filename), textureTarget(target), bindUnit(-1)
	{
		
	}

	Texture::Texture(const String& name, GLenum target, int width, int height) : Asset(name), 
		textureTarget(target), width(width), height(height), bindUnit(-1)
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