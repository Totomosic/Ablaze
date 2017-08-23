#pragma once
#include "AblazeGL.h"
#include "Types.h"
#include "Object.h"

namespace Ablaze
{

	struct RenderingSettings : public Object
	{
	public:
		bool useDepthTest;
		bool useBlend;
		GLenum depthFunction;
		GLenum blendSrcFunction;
		GLenum blendDstFunction;

		RenderingSettings();
		explicit RenderingSettings(bool useDepthTest, bool useBlend, GLenum depthFunction, GLenum blendSrcFunction, GLenum blendDstFunction);
		explicit RenderingSettings(bool useDepthTest, bool useBlend);
		explicit RenderingSettings(bool useDepthTest, GLenum depthFunction);
		explicit RenderingSettings(bool useBlend, GLenum blendSrcFunction, GLenum blendDstFunction);
		explicit RenderingSettings(GLenum depthFunction, GLenum blendSrcFunction, GLenum blendDstFunction);
		explicit RenderingSettings(GLenum blendSrcFunction, GLenum blendDstFunction);
		explicit RenderingSettings(GLenum depthFunction);

		void ApplySettings() const;

		String ToString() const override;

		static RenderingSettings Font();

	};

}