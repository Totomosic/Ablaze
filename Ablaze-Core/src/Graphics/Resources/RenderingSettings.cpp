#include "RenderingSettings.h"

namespace Ablaze
{

	RenderingSettings::RenderingSettings(bool useDepthTest, bool useBlend, GLenum depthFunction, GLenum blendSrcFunction, GLenum blendDstFunction)
		: useDepthTest(useDepthTest), useBlend(useBlend), depthFunction(depthFunction), blendSrcFunction(blendSrcFunction), blendDstFunction(blendDstFunction)
	{
	
	}

	RenderingSettings::RenderingSettings(bool useDepthTest, bool useBlend) : RenderingSettings(useDepthTest, useBlend, GL_LESS, GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA)
	{
	
	}

	RenderingSettings::RenderingSettings(bool useDepthTest, GLenum depthFunction) : RenderingSettings(useDepthTest, true, depthFunction, GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA)
	{
	
	}

	RenderingSettings::RenderingSettings(bool useBlend, GLenum blendSrcFunction, GLenum blendDstFunction) : RenderingSettings(true, useBlend, GL_LESS, blendSrcFunction, blendDstFunction)
	{
	
	}

	RenderingSettings::RenderingSettings(GLenum depthFunction, GLenum blendSrcFunction, GLenum blendDstFunction) : RenderingSettings(true, true, depthFunction, blendSrcFunction, blendDstFunction)
	{
	
	}

	RenderingSettings::RenderingSettings(GLenum blendSrcFunction, GLenum blendDstFunction) : RenderingSettings((GLenum)GL_LESS, blendSrcFunction, blendDstFunction)
	{
	
	}

	RenderingSettings::RenderingSettings(GLenum depthFunction) : RenderingSettings(true, depthFunction)
	{
	
	}

	RenderingSettings::RenderingSettings() : RenderingSettings(GL_LESS)
	{
	
	}

	void RenderingSettings::ApplySettings() const
	{
		if (useDepthTest)
		{
			glEnable(GL_DEPTH_TEST);
			glDepthFunc(depthFunction);
		}
		else
		{
			glDisable(GL_DEPTH_TEST);
		}
		if (useBlend)
		{
			glEnable(GL_BLEND);
			glBlendFunc(blendSrcFunction, blendDstFunction);
		}
		else
		{
			glDisable(GL_BLEND);
		}
	}

	String RenderingSettings::ToString() const
	{
		return "RenderingSettings: Depth: " + std::to_string(useDepthTest) + " Blend: " + std::to_string(useBlend) + " Depth Function: " + std::to_string(depthFunction) + 
			" BlendSrc: " + std::to_string(blendSrcFunction) + " BlendDst: " + std::to_string(blendDstFunction);
	}

	RenderingSettings RenderingSettings::Font()
	{
		return RenderingSettings(GL_LEQUAL);
	}

}