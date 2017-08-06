#pragma once
#include "Texture.h"

namespace Ablaze
{

	class TextureCube : public Texture
	{
	public:
		TextureCube();

	private:
		void Create() override;

	};

}