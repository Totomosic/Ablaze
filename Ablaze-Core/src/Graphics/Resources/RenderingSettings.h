#pragma once
#include "Types.h"
#include "Object.h"
#include "Utils/GLStates.h"

namespace Ablaze
{

	struct RenderingSettings : public Object
	{
	public:
		bool useDepthTest;
		bool useBlend;
		DepthFunc depthFunction;
		BlendSrcFunc blendSrcFunction;
		BlendDstFunc blendDstFunction;

		RenderingSettings();
		explicit RenderingSettings(bool useDepthTest, bool useBlend, DepthFunc depthFunction, BlendSrcFunc blendSrcFunction, BlendDstFunc blendDstFunction);
		explicit RenderingSettings(bool useDepthTest, bool useBlend);
		explicit RenderingSettings(bool useDepthTest, DepthFunc depthFunction);
		explicit RenderingSettings(bool useBlend, BlendSrcFunc blendSrcFunction, BlendDstFunc blendDstFunction);
		explicit RenderingSettings(DepthFunc depthFunction, BlendSrcFunc blendSrcFunction, BlendDstFunc blendDstFunction);
		explicit RenderingSettings(BlendSrcFunc blendSrcFunction, BlendDstFunc blendDstFunction);
		explicit RenderingSettings(DepthFunc depthFunction);

		void ApplySettings() const;

		String ToString() const override;

		static RenderingSettings Font();

	};

}