#include "RenderingSettings.h"

namespace Ablaze
{

	RenderingSettings::RenderingSettings(bool useDepthTest, bool useBlend, DepthFunc depthFunction, BlendSrcFunc blendSrcFunction, BlendDstFunc blendDstFunction)
		: useDepthTest(useDepthTest), useBlend(useBlend), depthFunction(depthFunction), blendSrcFunction(blendSrcFunction), blendDstFunction(blendDstFunction)
	{
	
	}

	RenderingSettings::RenderingSettings(bool useDepthTest, bool useBlend) : RenderingSettings(useDepthTest, useBlend, DepthFunc::Less, BlendSrcFunc::SrcAlpha, BlendDstFunc::OneMinusSrcAlpha)
	{
	
	}

	RenderingSettings::RenderingSettings(bool useDepthTest, DepthFunc depthFunction) : RenderingSettings(useDepthTest, true, depthFunction, BlendSrcFunc::SrcAlpha, BlendDstFunc::OneMinusSrcAlpha)
	{
	
	}

	RenderingSettings::RenderingSettings(bool useBlend, BlendSrcFunc blendSrcFunction, BlendDstFunc blendDstFunction) : RenderingSettings(true, useBlend, DepthFunc::Less, blendSrcFunction, blendDstFunction)
	{
	
	}

	RenderingSettings::RenderingSettings(DepthFunc depthFunction, BlendSrcFunc blendSrcFunction, BlendDstFunc blendDstFunction) : RenderingSettings(true, true, depthFunction, blendSrcFunction, blendDstFunction)
	{
	
	}

	RenderingSettings::RenderingSettings(BlendSrcFunc blendSrcFunction, BlendDstFunc blendDstFunction) : RenderingSettings(DepthFunc::Less, blendSrcFunction, blendDstFunction)
	{
	
	}

	RenderingSettings::RenderingSettings(DepthFunc depthFunction) : RenderingSettings(true, depthFunction)
	{
	
	}

	RenderingSettings::RenderingSettings() : RenderingSettings(DepthFunc::Less)
	{
	
	}

	void RenderingSettings::ApplySettings() const
	{
		GLStates::SetDepthTest(useDepthTest);
		GLStates::SetBlend(useBlend);
		GLStates::SetDepthFunction(depthFunction);
		GLStates::SetBlendSrcFunction(blendSrcFunction);
		GLStates::SetBlendDstFunction(blendDstFunction);
	}

	String RenderingSettings::ToString() const
	{
		return "RenderingSettings: Depth: " + std::to_string(useDepthTest) + " Blend: " + std::to_string(useBlend);
	}

	RenderingSettings RenderingSettings::Font()
	{
		return RenderingSettings(DepthFunc::LEqual);
	}

}