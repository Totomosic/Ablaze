#pragma once
#include "Scene/Layer.h"
#include "Graphics/Imaging/Textures/Texture.h"

namespace Ablaze
{

	static class DebugLayer
	{
	private:
		static Layer* debugLayer;
		static bool enabled;

	public:
		DebugLayer() = delete;

		static void Enable();
		static void Disable();

		static void RenderTexture(Texture* const texture, const maths::vec2& position, const maths::vec2& size);

	};

}