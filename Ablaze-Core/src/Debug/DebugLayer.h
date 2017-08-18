#pragma once
#include "Scene/Layer.h"
#include "Graphics/Resources/Imaging/Textures/Texture.h"
#include "Graphics/Resources/Shaders/Shader.h"
#include "Graphics/Resources/Models/Rectangle.h"

namespace Ablaze
{

	class DebugLayer
	{
	private:
		static Shader* textureShader;

	public:
		DebugLayer() = delete;

		static void Initialise();
		static void RenderTexture(Texture* const texture, const maths::vec2& position, const maths::vec2& size);

	};

}