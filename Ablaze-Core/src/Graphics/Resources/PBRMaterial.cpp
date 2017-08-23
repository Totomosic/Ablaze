#include "PBRMaterial.h"

namespace Ablaze
{

	PBRMaterial::PBRMaterial(const String& name, const Color& color, const Shader* const shader, Texture* albedo, Texture* roughness, Texture* metallic, Texture* ao, Texture* normalMap, const RenderingSettings& settings) 
		: Material(name, color, shader, settings)
	{
		AddTexture("albedoMap", albedo);
		AddTexture("roughnessMap", roughness);
		AddTexture("metallicMap", metallic);
		AddTexture("aoMap", ao);
		AddTexture("normalMap", normalMap);
	}

}