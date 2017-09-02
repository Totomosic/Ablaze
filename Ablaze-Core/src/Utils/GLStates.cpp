#include "GLStates.h"

namespace Ablaze
{

	bool GLStates::useDepthTest = false;
	bool GLStates::useBlend = false;
	DepthFunc GLStates::depthFunction = DepthFunc::Less;
	BlendSrcFunc GLStates::blendSrcFunction = BlendSrcFunc::SrcAlpha;
	BlendDstFunc GLStates::blendDstFunction = BlendDstFunc::OneMinusSrcAlpha;
	bool* GLStates::clipDistances = new bool[6];
	int GLStates::maxClipDistances = 6;

	void GLStates::Reset()
	{
		useDepthTest = false;
		useBlend = false;
		depthFunction = DepthFunc::Less;
		blendSrcFunction = BlendSrcFunc::SrcAlpha;
		blendDstFunction = BlendDstFunc::OneMinusSrcAlpha;
		for (int i = 0; i < maxClipDistances; i++)
		{
			clipDistances[i] = false;
			glDisable(GL_CLIP_DISTANCE0 + i);
		}
		glDisable(GL_DEPTH_TEST);
		glDisable(GL_BLEND);
		glDepthFunc((GLenum)depthFunction);
		glBlendFunc((GLenum)blendSrcFunction, (GLenum)blendDstFunction);
	}

	bool GLStates::DepthTest()
	{
		return useDepthTest;
	}

	bool GLStates::Blend()
	{
		return useBlend;
	}

	DepthFunc GLStates::DepthFunction()
	{
		return depthFunction;
	}

	BlendSrcFunc GLStates::BlendSrcFunction()
	{
		return blendSrcFunction;
	}

	BlendDstFunc GLStates::BlendDstFunction()
	{
		return blendDstFunction;
	}

	bool GLStates::ClipDistance(int index)
	{
		return clipDistances[index];
	}

	int GLStates::MaxClipDistances()
	{
		return maxClipDistances;
	}

	void GLStates::SetDepthTest(bool state)
	{
		if (state != useDepthTest)
		{
			useDepthTest = state;
			if (useDepthTest)
			{
				glEnable(GL_DEPTH_TEST);
			}
			else
			{
				glDisable(GL_DEPTH_TEST);
			}
		}
	}

	void GLStates::SetBlend(bool state)
	{
		if (state != useBlend)
		{
			useBlend = state;
			if (useBlend)
			{
				glEnable(GL_BLEND);
			}
			else
			{
				glDisable(GL_BLEND);
			}
		}
	}

	void GLStates::SetDepthFunction(DepthFunc function)
	{
		if (function != depthFunction)
		{
			depthFunction = function;
			glDepthFunc((GLenum)depthFunction);
		}
	}

	void GLStates::SetBlendSrcFunction(BlendSrcFunc function)
	{
		if (function != blendSrcFunction)
		{
			blendSrcFunction = function;
			glBlendFunc((GLenum)blendSrcFunction, (GLenum)blendDstFunction);
		}
	}

	void GLStates::SetBlendDstFunction(BlendDstFunc function)
	{
		if (function != blendDstFunction)
		{
			blendDstFunction = function;
			glBlendFunc((GLenum)blendSrcFunction, (GLenum)blendDstFunction);
		}
	}

	void GLStates::SetClipDistance(int index, bool state)
	{
		if (clipDistances[index] != state)
		{
			clipDistances[index] = state;
			if (state)
			{
				glEnable(GL_CLIP_DISTANCE0 + index);
			}
			else
			{
				glDisable(GL_CLIP_DISTANCE0 + index);
			}
		}
	}

	void GLStates::EnableDepthTest()
	{
		SetDepthTest(true);
	}

	void GLStates::EnableBlend()
	{
		SetBlend(true);
	}

	void GLStates::EnableClipDistance(int index)
	{
		SetClipDistance(index, true);
	}

	void GLStates::DisableDepthTest()
	{
		SetDepthTest(false);
	}

	void GLStates::DisableBlend()
	{
		SetBlend(false);
	}

	void GLStates::DisableClipDistance(int index)
	{
		SetClipDistance(index, false);
	}

}