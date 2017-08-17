#pragma once
#include "Widget.h"
#include "Graphics/Resources/Fonts/Font.h"

namespace Ablaze
{

	class Text : public Widget
	{
	private:

	public:
		Text(const String& text, Font* font, const Color& color = Color::White());
		Text(const maths::vec3& position, const String& text, Font* font, const Color& color = Color::White());
		Text(float x, float y, float z, const String& text, Font* font, const Color& color = Color::White());
		Text(const maths::vec2& position, const String& text, Font* font, const Color& color = Color::White());
		Text(float x, float y, const String& text, Font* font, const Color& color = Color::White());
		
		Components::TextComponent* TextComponent() const;

		void SetText(const String& text);
		void SetFont(Font* font);
		void SetColor(const Color& color);

	};

}