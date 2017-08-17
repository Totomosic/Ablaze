#include "PBRMaterial.h"

namespace Ablaze
{

	PBRMaterial::PBRMaterial(const String& name, const Color& color, const Shader* const shader, Texture* albedo, Texture* roughness, Texture* metallic, Texture* ao, Texture* normalMap, 
		bool depthState, bool blendState, GLenum depthFunction, GLenum srcBlendState, GLenum dstBlendState) : Material(name, color, shader, "", nullptr, depthState, blendState, depthFunction, srcBlendState, dstBlendState)
	{
		AddTexture("albedoMap", albedo);
		AddTexture("roughnessMap", roughness);
		AddTexture("metallicMap", metallic);
		AddTexture("aoMap", ao);
		AddTexture("normalMap", normalMap);
	}

}