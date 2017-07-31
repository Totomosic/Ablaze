#pragma once
#include "PostProcessorEffect.h"
#include "Graphics\Context.h"

namespace Ablaze
{

	class PostProcessor
	{
	private:
		static Framebuffer* fbo;

	public:
		static const Framebuffer* Apply(const PostProcessorEffect& effect, Texture2D* frame, int width = Context::Window()->GetWidth(), int height = Context::Window()->GetHeight());

	};

}