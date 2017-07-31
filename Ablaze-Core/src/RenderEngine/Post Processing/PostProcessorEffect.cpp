#include "PostProcessorEffect.h"

namespace Ablaze
{

	PostProcessorEffect::PostProcessorEffect(const String& name, Shader* shader)
		: name(name), effectShader(shader)
	{
	
	}

	Shader* PostProcessorEffect::GetShader() const
	{
		return effectShader;
	}

	const String& PostProcessorEffect::GetName() const
	{
		return name;
	}

}