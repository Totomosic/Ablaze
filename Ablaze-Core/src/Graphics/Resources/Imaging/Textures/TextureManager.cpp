#include "TextureManager.h"

namespace Ablaze
{

	std::unordered_map<int, Texture*> TextureManager::bindings = std::unordered_map<int, Texture*>();
	GLint TextureManager::maxTextureUnits = 0;
	GLint TextureManager::usedTextures = 0;
	GLint TextureManager::currentTexture = -1;

	void TextureManager::Initialise()
	{
		glGetIntegerv(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, &maxTextureUnits);
	}

	void TextureManager::Bind(Texture* texture)
	{
		if (usedTextures < maxTextureUnits)
		{
			if (texture->GetBindUnit() == -1)
			{
				bindings[usedTextures] = texture;
				texture->SetBindUnit(usedTextures);
				glActiveTexture(GL_TEXTURE0 + usedTextures);
				glBindTexture(texture->textureTarget, texture->GetID());
				currentTexture = usedTextures;
				usedTextures++;
			}
			else if (currentTexture != texture->GetBindUnit())
			{
				currentTexture = texture->GetBindUnit();
				glActiveTexture(GL_TEXTURE0 + currentTexture);
			}
		}
		else
		{
			// Run out of textures
			AB_ERROR("Out of texture units needs fix");
		}
	}

	void TextureManager::Unbind(Texture* texture)
	{
		
	}

}