#include "TextureFactory.h"

namespace Ablaze
{

	std::unordered_map<String, std::pair<Texture*, int>*> TextureFactory::textures = std::unordered_map<String, std::pair<Texture*, int>*>();

	Texture2D* TextureFactory::Request2D(const String& name)
	{
		if (ContainsKey(name))
		{
			auto pair = textures[name];
			pair->second += 1;
			return (Texture2D*)pair->first;
		}
		AB_ERROR("Attempted to request Texture2D that does not exist: " + name);
		return nullptr;
	}

	Texture2D* TextureFactory::Request2D(Texture2D* texture)
	{
		return Request2D(texture->GetName());
	}

	bool TextureFactory::Release2D(const String& name)
	{
		if (ContainsKey(name))
		{
			auto pair = textures[name];
			pair->second -= 1;
			if (pair->second <= 0)
			{
				textures.erase(name);
				delete pair->first;
				delete pair;
				return true;
			}
			return false;
		}
		AB_WARN("Attempted to release Texture2D that does not exist: " + name);
		return false;
	}

	Texture2D* TextureFactory::Request2DWeak(const String& name)
	{
		Texture2D* tex = Request2D(name);
		Decrement(tex->GetName());
		return tex;
	}

	Texture2D* TextureFactory::Request2DWeak(Texture2D* texture)
	{
		return Request2DWeak(texture->GetName());
	}

	bool TextureFactory::Release2D(Texture2D* texture)
	{
		return Release2D(texture->GetName());
	}

	Texture2D* TextureFactory::Build2D(const String& name, const ImageFile* const file)
	{
		Texture2D* texture = new Texture2D(name, file->GetPath());
		CreateNew(texture, 1);
		return texture;
	}

	void TextureFactory::Order2D(const String& name, const ImageFile* const file)
	{
		Decrement(Build2D(name, file)->GetName());
	}

	int TextureFactory::RequestReferenceCount(const String& name)
	{
		if (ContainsKey(name))
		{
			return textures[name]->second;
		}
		AB_WARN("Attempted to get reference count of texture that does not exist: " + name);
		return 0;
	}

	void TextureFactory::Increment(const String& name)
	{
		textures[name]->second += 1;
	}

	void TextureFactory::Decrement(const String& name)
	{
		textures[name]->second -= 1;
	}

	bool TextureFactory::ContainsKey(const String& name)
	{
		return textures.find(name) != textures.end();
	}

	void TextureFactory::CreateNew(Texture* texture, int refCount)
	{
		textures[texture->GetName()] = new std::pair<Texture*, int>(texture, refCount);
	}

}