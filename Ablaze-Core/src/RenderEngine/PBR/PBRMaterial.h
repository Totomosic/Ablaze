#pragma once
#include "RenderEngine/structs/Material.h"

namespace Ablaze
{

	class MaterialFactory;

	class PBRMaterial : public Material
	{
	protected:
		PBRMaterial(const String& name, const Color& color, const Shader* const shader, Texture* albedo, Texture* roughness, Texture* metallic, Texture* ao, Texture* normalMap,
			bool depthState, bool blendState, GLenum depthFunction, GLenum srcBlendState, GLenum dstBlendState);

	public:
		friend class MaterialFactory;

	};

}