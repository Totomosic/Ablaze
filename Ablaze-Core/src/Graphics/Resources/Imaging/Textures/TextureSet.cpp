#include "TextureSet.h"

namespace Ablaze
{

	TextureSet::TextureSet()
	{
	
	}

	TextureSet::TextureSet(const String& sampler, Texture* texture)
	{
		AddTexture(sampler, texture);
	}

	TextureSet::~TextureSet()
	{
		for (auto pair : textures)
		{
			delete pair;
		}
	}

	void TextureSet::AddTexture(const String& sampler, Texture* texture)
	{
		textures.push_back(new std::pair<String, Texture*>(sampler, texture));
	}

}