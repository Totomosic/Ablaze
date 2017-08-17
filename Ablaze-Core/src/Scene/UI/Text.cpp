#include "Text.h"

namespace Ablaze
{

	Text::Text(const maths::vec3& position, const String& text, Font* font, const Color& color) : Widget(position, font->GetSize(text))
	{
		AddComponent(new Components::TextComponent(text, font, color));
	}

	Text::Text(float x, float y, float z, const String& text, Font* font, const Color& color) : Text(maths::vec3(x, y, z), text, font, color)
	{
	
	}

	Text::Text(const maths::vec2& position, const String& text, Font* font, const Color& color) : Text(maths::vec3(position, 0), text, font, color)
	{
	
	}

	Text::Text(float x, float y, const String& text, Font* font, const Color& color) : Text(x, y, 0, text, font, color)
	{
	
	}

	Text::Text(const String& text, Font* font, const Color& color) : Text(0, 0, text, font, color)
	{
	
	}

	Components::TextComponent* Text::TextComponent() const
	{
		return GetComponent<Components::TextComponent>();
	}

	void Text::SetText(const String& text)
	{
		TextComponent()->SetText(text);
	}

	void Text::SetFont(Font* font)
	{
		TextComponent()->SetFont(font);
	}

	void Text::SetColor(const Color& color)
	{
		TextComponent()->SetColor(color);
	}	

}