#pragma once
#include "Scene/Layer.h"
#include "Graphics/Imaging/Textures/Texture.h"
#include "Graphics/Shaders/Shader.h"
#include "RenderEngine/Models/Rectangle.h"

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