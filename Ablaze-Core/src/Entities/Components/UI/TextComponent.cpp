#include "TextComponent.h"
#include "Entities/Components/Rendering/MeshComponent.h"
#include "Entities/GameObject.h"

namespace Ablaze
{
	namespace Components
	{

		TextComponent::TextComponent(const String& text, Font* font, const Color& color) : Component(),
			text(text), font(font), color(color)
		{
		
		}

		TextComponent::~TextComponent()
		{
			FontFactory::Release(font);
		}

		void TextComponent::Initialise()
		{
			ApplyToMesh();
		}

		const String& TextComponent::GetText() const
		{
			return text;
		}

		const Font* TextComponent::GetFont() const
		{
			return font;
		}

		const Color& TextComponent::GetColor() const
		{
			return color;
		}

		void TextComponent::SetText(const String& text)
		{
			this->text = text;
			ApplyToMesh();
		}

		void TextComponent::SetFont(Font* font)
		{
			this->font = font;
			ApplyToMesh();
		}

		void TextComponent::SetColor(const Color& color)
		{
			this->color = color;
			owner->Mesh()->GetMesh()->GetModel(0)->SetColor(color);
		}

		Component* TextComponent::Clone()
		{
			TextComponent* txt = new TextComponent(text, font, color);
			return txt;
		}

		void TextComponent::ApplyToMesh()
		{
			if (owner->HasComponent<Components::MeshComponent>())
			{
				owner->SetMesh(MeshFactory::BuildTextUnnamed(text, font, color, MaterialFactory::FabricateFont(Color::White(), Shader::Font(), "Tex0", font)));
			}
			else
			{
				owner->AddComponent(new Components::MeshComponent(MeshFactory::BuildTextUnnamed(text, font, color, MaterialFactory::FabricateFont(Color::White(), Shader::Font(), "Tex0", font))));
			}
		}

	}
}