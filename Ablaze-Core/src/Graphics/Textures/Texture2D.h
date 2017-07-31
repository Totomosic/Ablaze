#pragma once
#include "Texture.h"

namespace Ablaze
{
	class Texture2D : public Texture
	{
	private:

	protected:
		Texture2D(const String& name, const String& path);
		Texture2D(const String& name, int width, int height);

	public:
		friend class TextureFactory;
		friend class Framebuffer;
		friend class TextureManager;

	protected:
		void Create() override;
	};

}