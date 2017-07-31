#include "FontFactory.h"

namespace Ablaze
{

	std::unordered_map<String, std::unordered_map<float, std::pair<Font*, int>*>*> FontFactory::fonts = std::unordered_map<String, std::unordered_map<float, std::pair<Font*, int>*>*>();

	Font* FontFactory::Request(const String& fontName, float size)
	{
		if (ContainsFont(fontName))
		{
			if (ContainsSize(fontName, size))
			{
				auto val = *(fonts[fontName]);
				auto pair = val[size];
				pair->second += 1;
				return pair->first;
			}
			else
			{
				// Type of font exists but in wrong size
				std::vector<float> sizes;
				for (auto it = fonts[fontName]->begin(); it != fonts[fontName]->end(); ++it) {
					sizes.push_back(it->first);
					break;
				}
				auto font = (*(fonts[fontName]))[sizes[0]];
				AB_INFO("Unable to find font of type: " + fontName + " with size of: " + std::to_string(size) + ", new font was created.");
				return Build(fontName, font->first->GetPath(), size);
			}
		}
		AB_ERROR("Attempted to request a font that does not exist: " + fontName);
		return nullptr;
	}

	Font* FontFactory::Request(Font* font)
	{
		return Request(font->GetName(), font->GetSize());
	}

	Font* FontFactory::RequestWeak(const String& fontName, float size)
	{
		Font* font = Request(fontName, size);
		Decrement(fontName, size);
		return font;
	}

	Font* FontFactory::RequestWeak(Font* font)
	{
		return RequestWeak(font->GetName(), font->GetSize());
	}

	bool FontFactory::Release(const String& fontName, float size)
	{
		if (ContainsSize(fontName, size))
		{
			auto val = *(fonts[fontName]);
			auto pair = val[size];
			pair->second--;
			if (pair->second <= 0)
			{
				delete pair->first;
				delete pair;
				val.erase(size);
				if (val.empty())
				{
					delete &val;
					fonts.erase(fontName);
				}
				return true;
			}
			return false;
		}
		AB_WARN("Attempted to release a font that does not exist: " + fontName);
		return false;
	}

	bool FontFactory::Release(Font* font)
	{
		return Release(font->GetName(), font->GetSize());
	}

	Font* FontFactory::Build(const String& fontName, const String& filename, float size)
	{
		Font* font = new Font(fontName, filename, size);
		CreateNew(font, 1);
		return font;
	}

	void FontFactory::Order(const String& fontName, const String& filename, float size)
	{
		Font* font = Build(fontName, filename, size);
		Decrement(font->GetName(), font->GetSize());
	}

	int FontFactory::RequestReferenceCount(const String& fontName, float size)
	{
		if (ContainsSize(fontName, size))
		{
			return (*(fonts[fontName]))[size]->second;
		}
		AB_WARN("Attempted to get reference count of font that does not exist: " + fontName + ", " + std::to_string(size));
		return 0;
	}

	bool FontFactory::Exists(const String& fontName, float size)
	{
		return ContainsSize(fontName, size);
	}

	bool FontFactory::Exists(const String& fontName)
	{
		return ContainsFont(fontName);
	}

	bool FontFactory::Exists(Font* font)
	{
		return ContainsSize(font->GetName(), font->GetSize());
	}

	int FontFactory::RequestReferenceCount(Font* font)
	{
		return RequestReferenceCount(font->GetName(), font->GetSize());
	}

	void FontFactory::Increment(const String& name, float size)
	{
		(*(fonts[name]))[size]->second++;
	}

	void FontFactory::Decrement(const String& name, float size)
	{
		(*(fonts[name]))[size]->second--;
	}

	void FontFactory::CreateNew(Font* font, int referenceCount)
	{
		if (fonts.find(font->GetName()) != fonts.end())
		{
			(*(fonts[font->GetName()]))[font->GetSize()] = new std::pair<Font*, int>(font, referenceCount);
		}
		else
		{
			fonts[font->GetName()] = new std::unordered_map<float, std::pair<Font*, int>*>();
			(*(fonts[font->GetName()]))[font->GetSize()] = new std::pair<Font*, int>(font, referenceCount);
		}
	}

	bool FontFactory::ContainsFont(const String& fontName)
	{
		if (fonts.find(fontName) != fonts.end())
		{
			return true;
		}
		return false;
	}

	bool FontFactory::ContainsSize(const String& name, float size)
	{
		if (ContainsFont(name))
		{
			auto otherMap = fonts[name];
			if (otherMap->find(size) != otherMap->end())
			{
				return true;
			}
			return false;
		}
		return false;
	}

}