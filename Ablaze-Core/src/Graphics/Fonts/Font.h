#pragma once
#include "structs/Structs.h"
#include "RenderEngine/RenderEngine.h"
#include "Graphics/Imaging/Textures/Texture.h"
#include "Utils/Files/FontFile.h"
#include "Types.h"

namespace Ablaze
{
	
	class Font : public Texture
	{
	private:
		ftgl::texture_atlas_t* FTAtlas;
		ftgl::texture_font_t* FTFont;
		float size;

	public:
		Font(const String& name, String filename, float size = 32);
		~Font() override;

		float GetSize() const;

		float GetWidth(const String& text) const;
		float GetHeight(const String& text) const;

		Model* CreateModel(const String& modelName, const String& text, const Color& color = Color::White()) const;

	private:
		void Create() override;

	};

}