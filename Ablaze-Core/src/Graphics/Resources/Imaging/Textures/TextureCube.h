#pragma once
#include "Texture.h"

namespace Ablaze
{

	class TextureCube : public Texture
	{
	public:
		TextureCube(const String& name);

	private:
		void Create() override;

	};

} 