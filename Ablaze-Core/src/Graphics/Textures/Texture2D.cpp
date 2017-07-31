#include "Texture2D.h"

namespace Ablaze
{

	Texture2D::Texture2D(const String& name, const String& path) : Texture(name, path, GL_TEXTURE_2D)
	{
		Create();
	}

	Texture2D::Texture2D(const String& name, int width, int height) : Texture(name, GL_TEXTURE_2D, width, height)
	{
		glGenTextures(1, &id);
	}

	void Texture2D::Create()
	{
		glGenTextures(1, &id);
		uint bpp = 0;
		Texture::Create();
		BYTE* pixels = LoadTextureImage(path.c_str(), &width, &height, &bpp);
		Bind();
		glTexParameteri(textureTarget, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(textureTarget, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		switch (bpp)
		{
		case 32:
			glTexImage2D(textureTarget, 0, GL_RGBA, width, height, 0, GL_BGRA, GL_UNSIGNED_BYTE, pixels);
			break;
		case 24:
			glTexImage2D(textureTarget, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, pixels);
			break;
		case 16:
			glTexImage2D(textureTarget, 0, GL_RED, width, height, 0, GL_RED, GL_UNSIGNED_BYTE, pixels);
			break;
		case 8:
			glTexImage2D(textureTarget, 0, GL_RED, width, height, 0, GL_RED, GL_UNSIGNED_BYTE, pixels);
			break;
		}
		glGenerateMipmap(textureTarget);
		delete[] pixels;
	}

}