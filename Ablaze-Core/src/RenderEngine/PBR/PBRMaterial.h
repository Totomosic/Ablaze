#pragma once
#include "RenderEngine/structs/Material.h"

namespace Ablaze
{

	class MaterialFactory;

	class PBRMaterial : public Material
	{
	protected:
		PBRMaterial(const String& name, const Color& color, const Shader* const shader, Texture* albedo, Texture* roughness, Texture* metallic, Texture* ao, Texture* normalMap, bool depthState = true, bool blendState = true, GLenum srcBlendState = GL_SRC_ALPHA, GLenum dstBlendState = GL_ONE_MINUS_SRC_ALPHA);

	public:
		void ApplyMaterial() const;

		friend class MaterialFactory;

	};

}