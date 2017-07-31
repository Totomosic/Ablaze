#pragma once
#include "Texture.h"
#include "Types.h"

namespace Ablaze
{

	class TextureManager
	{
	private:
		static std::unordered_map<int, Texture*> bindings;
		static GLint maxTextureUnits;
		static GLint usedTextures;
		static GLint currentTexture;

	public:
		TextureManager() { }

		static void Initialise();

		static void Bind(Texture* texture);
		static void Unbind(Texture* texture);

	};

}