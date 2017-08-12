#include "MaterialFactory.h"

namespace Ablaze
{

	std::unordered_map<String, std::pair<Material*, int>*> MaterialFactory::materials = std::unordered_map<String, std::pair<Material*, int>*>();

	Material* MaterialFactory::Request(const String& name)
	{
		if (ContainsKey(name))
		{
			auto pair = materials[name];
			pair->second += 1;
			return pair->first;
		}
		AB_ERROR("Attempted to request material that does not exist: " + name);
		return nullptr;
	}

	Material* MaterialFactory::Request(const Material* const material)
	{
		return Request(material->GetName());
	}

	PBRMaterial* MaterialFactory::RequestPBR(const String& name)
	{
		return (PBRMaterial*)Request(name);
	}

	PBRMaterial* MaterialFactory::RequestPBR(const PBRMaterial* const material)
	{
		return RequestPBR(material->GetName());
	}

	bool MaterialFactory::Release(const String& name)
	{
		if (ContainsKey(name))
		{
			auto pair = materials[name];
			pair->second -= 1;
			if (pair->second <= 0)
			{
				materials.erase(name);
				delete pair->first;
				delete pair;
				return true;
			}
			return false;
		}
		AB_WARN("Attempted to release material that does not exist: " + name);
		return false;
	}

	bool MaterialFactory::Release(const Material* const material)
	{
		return Release(material->GetName());
	}

	bool MaterialFactory::ReleasePBR(const String& name)
	{
		return Release(name);
	}

	bool MaterialFactory::ReleasePBR(const PBRMaterial* const material)
	{
		return Release(material);
	}

	Material* MaterialFactory::Build(const String& name, const Color& color, const Shader* const shader, const String& sampler, Texture* texture, bool depth, bool blend, GLenum blendSrcFunc, GLenum blendDstFunc)
	{
		Material* mat = new Material(name, color, shader, sampler, texture, depth, blend, blendSrcFunc, blendDstFunc);
		CreateNew(mat, 1);
		return mat;
	}

	Material* MaterialFactory::Build(const String& name, const Color& color, const Shader* const shader, const String& sampler, const String& textureName, bool depth, bool blend, GLenum blendSrcFunc, GLenum blendDstFunc)
	{
		return Build(name, color, shader, sampler, TextureFactory::Request2D(textureName), depth, blend, blendSrcFunc, blendDstFunc);
	}

	Material* MaterialFactory::Build(const String& name, const Color& color, const Shader* const shader, const TextureSet& textures, bool depth, bool blend, GLenum blendSrcFunc, GLenum blendDstFunc)
	{
		Material* mat = new Material(name, color, shader, textures, depth, blend, blendSrcFunc, blendDstFunc);
		CreateNew(mat, 1);
		return mat;
	}

	PBRMaterial* MaterialFactory::BuildPBR(const String& name, const Color& color, const Shader* const shader, Texture* albedo, Texture* roughness, Texture* metallic, Texture* ao, Texture* normalMap,
		bool depth, bool blend, GLenum blendSrcFunc, GLenum blendDstFunc)
	{
		PBRMaterial* mat = new PBRMaterial(name, color, shader, albedo, roughness, metallic, ao, normalMap, depth, blend, blendSrcFunc, blendDstFunc);
		CreateNew(mat, 1);
		return mat;
	}

	PBRMaterial* MaterialFactory::BuildPBR(const String& name, const Color& color, const Shader* const shader, const String& albedoTexture, const String& roughnessTexture, const String& metallicTexture, const String& aoTexture, const String& normalMap,
		bool depth, bool blend, GLenum blendSrcFunc, GLenum blendDstFunc)
	{
		return BuildPBR(name, color, shader, TextureFactory::Request2D(albedoTexture), TextureFactory::Request2D(roughnessTexture), TextureFactory::Request2D(metallicTexture), TextureFactory::Request2D(aoTexture), TextureFactory::Request2D(normalMap), depth, blend, blendSrcFunc, blendDstFunc);
	}

	void MaterialFactory::Order(const String& name, const Color& color, const Shader* const shader, const String& sampler, Texture* texture, bool depth, bool blend, GLenum blendSrcFunc, GLenum blendDstFunc)
	{
		Decrement(Build(name, color, shader, sampler, texture, depth, blend, blendSrcFunc, blendDstFunc)->GetName());
	}

	void MaterialFactory::Order(const String& name, const Color& color, const Shader* const shader, const String& sampler, const String& textureName, bool depth, bool blend, GLenum blendSrcFunc, GLenum blendDstFunc)
	{
		Order(name, color, shader, sampler, TextureFactory::Request2D(textureName), depth, blend, blendSrcFunc, blendDstFunc);
	}

	void MaterialFactory::Order(const String& name, const Color& color, const Shader* const shader, const TextureSet& textures, bool depth, bool blend, GLenum blendSrcFunc, GLenum blendDstFunc)
	{
		Decrement(Build(name, color, shader, textures, depth, blend, blendSrcFunc, blendDstFunc)->GetName());
	}

	void MaterialFactory::OrderPBR(const String& name, const Color& color, const Shader* const shader, Texture* albedo, Texture* roughness, Texture* metallic, Texture* ao, Texture* normalMap,
		bool depth, bool blend, GLenum blendSrcFunc, GLenum blendDstFunc)
	{
		Decrement(BuildPBR(name, color, shader, albedo, roughness, metallic, ao, normalMap, depth, blend, blendSrcFunc, blendDstFunc)->GetName());
	}

	void MaterialFactory::OrderPBR(const String& name, const Color& color, const Shader* const shader, const String& albedoTexture, const String& roughnessTexture, const String& metallicTexture, const String& aoTexture, const String& normalMap,
		bool depth, bool blend, GLenum blendSrcFunc, GLenum blendDstFunc)
	{
		OrderPBR(name, color, shader, TextureFactory::Request2D(albedoTexture), TextureFactory::Request2D(roughnessTexture), TextureFactory::Request2D(metallicTexture), TextureFactory::Request2D(aoTexture), TextureFactory::Request2D(normalMap), depth, blend, blendSrcFunc, blendDstFunc);
	}

	void MaterialFactory::Increment(const String& name)
	{
		materials[name]->second++;
	}

	void MaterialFactory::Decrement(const String& name)
	{
		materials[name]->second--;
	}

	void MaterialFactory::CreateNew(Material* material, int refCount)
	{
		materials[material->GetName()] = new std::pair<Material*, int>(material, refCount);
	}

	bool MaterialFactory::ContainsKey(const String& name)
	{
		return materials.find(name) != materials.end();
	}

}