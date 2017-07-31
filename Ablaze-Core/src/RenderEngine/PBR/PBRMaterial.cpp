#include "PBRMaterial.h"

namespace Ablaze
{

	PBRMaterial::PBRMaterial(const String& name, const Color& color, const Shader* const shader, Texture* albedo, Texture* roughness, Texture* metallic, Texture* ao, Texture* normalMap, bool depthState, bool blendState, GLenum srcBlendState, GLenum dstBlendState)
		: Material(name, color, shader, nullptr, depthState, blendState, srcBlendState, dstBlendState)
	{
		AddTexture(albedo);
		AddTexture(roughness);
		AddTexture(metallic);
		AddTexture(ao);
		AddTexture(normalMap);
	}

	void PBRMaterial::ApplyMaterial() const
	{
		shader->Enable();
		if (depthState)
		{
			glEnable(GL_DEPTH_TEST);
		}
		else
		{
			glDisable(GL_DEPTH_TEST);
		}
		if (blendState)
		{
			glEnable(GL_BLEND);
			glBlendFunc(srcBlendState, dstBlendState);
		}
		else
		{
			glDisable(GL_BLEND);
		}
		shader->SetTexture(*(textures[0]), "albedo");
		shader->SetTexture(*(textures[1]), "roughness");
		shader->SetTexture(*(textures[2]), "metallic");
		shader->SetTexture(*(textures[3]), "ao");
		shader->SetTexture(*(textures[4]), "normalMap");
	}

}