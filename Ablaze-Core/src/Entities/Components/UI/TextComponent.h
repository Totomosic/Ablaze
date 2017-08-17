#pragma once
#include "../Component.h"
#include "Graphics/Resources/Fonts/Font.h"
#include "Factories/FontFactory.h"
#include "Factories/MeshFactory.h"

namespace Ablaze
{
	namespace Components
	{
		// Interacts with mesh component to setup text mesh
		class TextComponent : public Component
		{
		private:
			String text;
			Font* font;
			Color color;

		public:
			TextComponent(const String& text, Font* font, const Color& color = Color::White());
			~TextComponent();

			void Initialise() override;

			const String& GetText() const;
			const Font* GetFont() const;
			const Color& GetColor() const;

			void SetText(const String& text);
			void SetFont(Font* font);
			void SetColor(const Color& color);

			Component* Clone() override;

		private:
			void ApplyToMesh();

		};

	}
}