#pragma once
#include "Graphics/Resources/Shaders/Shader.h"
#include "Graphics/Resources/Imaging/Framebuffers/Framebuffer.h"
#include "Types.h"

namespace Ablaze
{

	class PostProcessorEffect
	{
	private:
		String name;
		Shader* effectShader;

	public:
		PostProcessorEffect(const String& name, Shader* effectShader);

		Shader* GetShader() const;
		const String& GetName() const;

	};

}