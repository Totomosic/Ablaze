#pragma once
#include "AblazeGL.h"

namespace Ablaze
{

	enum class DepthFunc : GLenum
	{
		Less = GL_LESS,
		LEqual = GL_LEQUAL,
		Equal = GL_EQUAL,
		GEqual = GL_GEQUAL,
		Greater = GL_GREATER
	};

	enum class BlendSrcFunc : GLenum
	{
		SrcAlpha = GL_SRC_ALPHA,
		One = GL_ONE
	};

	enum class BlendDstFunc : GLenum
	{
		OneMinusSrcAlpha = GL_ONE_MINUS_SRC_ALPHA,
		One = GL_ONE
	};

	class GLStates
	{
	private:
		static bool useDepthTest;
		static bool useBlend;
		static DepthFunc depthFunction;
		static BlendSrcFunc blendSrcFunction;
		static BlendDstFunc blendDstFunction;
		static bool* clipDistances;
		static int maxClipDistances;

	public:
		GLStates() = delete;

		static void Reset();

		static bool DepthTest();
		static bool Blend();
		static DepthFunc DepthFunction();
		static BlendSrcFunc BlendSrcFunction();
		static BlendDstFunc BlendDstFunction();
		static bool ClipDistance(int index);
		static int MaxClipDistances();

		static void SetDepthTest(bool state);
		static void SetBlend(bool state);
		static void SetDepthFunction(DepthFunc function);
		static void SetBlendSrcFunction(BlendSrcFunc function);
		static void SetBlendDstFunction(BlendDstFunc function);
		static void SetClipDistance(int index, bool state);

		static void EnableDepthTest();
		static void EnableBlend();
		static void EnableClipDistance(int index);

		static void DisableDepthTest();
		static void DisableBlend();
		static void DisableClipDistance(int index);

	};

}