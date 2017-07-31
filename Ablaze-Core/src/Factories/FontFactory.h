#pragma once
#include "Graphics\Fonts\Font.h"
#include "Log.h"
#include "Types.h"

namespace Ablaze
{

	class FontFactory
	{
	private:
		static std::unordered_map<String, std::unordered_map<float, std::pair<Font*, int>*>*> fonts;

	public:
		FontFactory() { }

		static Font* Request(const String& fontName, float size);
		static Font* Request(Font* font);
		static Font* RequestWeak(const String& fontName, float size);
		static Font* RequestWeak(Font* font);
		static bool Release(const String& fontName, float size);
		static bool Release(Font* font);

		static Font* Build(const String& fontName, const String& filename, float size);
		
		static void Order(const String& fontName, const String& filename, float size);

		static bool Exists(const String& fontName, float size);
		static bool Exists(const String& fontName);
		static bool Exists(Font* font);

		static int RequestReferenceCount(const String& fontName, float size);
		static int RequestReferenceCount(Font* font);

	private:
		static void Increment(const String& name, float size);
		static void Decrement(const String& name, float size);
		static void CreateNew(Font* font, int referenceCount);
		static bool ContainsFont(const String& fontName);
		static bool ContainsSize(const String& fontName, float size);

	};

}