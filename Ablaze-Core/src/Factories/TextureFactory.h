#pragma once
#include "Graphics\Textures\Texture2D.h"
#include "Graphics\Textures\TextureCube.h"
#include "Utils\Files\ImageFile.h"
#include <map>

namespace Ablaze
{

	class TextureFactory
	{
	private:
		static std::unordered_map<String, std::pair<Texture*, int>*> textures;

	public:
		TextureFactory() { }

		static Texture2D* Request2D(const String& name);
		static Texture2D* Request2D(Texture2D* texture);
		static bool Release2D(const String& name);
		static bool Release2D(Texture2D* texture);

		static Texture2D* Build2D(const String& name, const ImageFile* const file);
		static TextureCube* BuildCube(const String& name, const ImageFile* const file);

		static void Order2D(const String& name, const ImageFile* const file);
		static void OrderCube(const String& name, const ImageFile* const file);

		static int RequestReferenceCount(const String& name);

	private:
		static void Increment(const String& name);
		static void Decrement(const String& name);
		static bool ContainsKey(const String& name);
		static void CreateNew(Texture* texture, int referenceCount);

	};

}