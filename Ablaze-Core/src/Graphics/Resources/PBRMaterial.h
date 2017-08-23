#pragma once
#include "Material.h"

namespace Ablaze
{

	class PBRMaterial : public Material
	{
	protected:
		PBRMaterial(const String& name, const Color& color, const Shader* const shader, Texture* albedo, Texture* roughness, Texture* metallic, Texture* ao, Texture* normalMap,
			const RenderingSettings& settings = RenderingSettings());

	public:
		friend class MaterialFactory;

	};

}