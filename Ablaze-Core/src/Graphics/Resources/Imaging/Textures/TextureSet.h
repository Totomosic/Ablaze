#pragma once
#include "Texture.h"

namespace Ablaze
{

	struct TextureSet
	{
		std::vector<std::pair<String, Texture*>*> textures;

	public:
		TextureSet();
		TextureSet(const String& sampler, Texture* texture);
		~TextureSet();

		void AddTexture(const String& sampler, Texture* texture);

	};

}