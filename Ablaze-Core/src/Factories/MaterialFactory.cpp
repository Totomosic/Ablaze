#include "MaterialFactory.h"
#include "FontFactory.h"

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

	Material* MaterialFactory::Build(const String& name, const Color& color, const Shader* const shader, const String& sampler, Texture* texture, const RenderingSettings& settings)
	{
		Material* mat = new Material(name, color, shader, sampler, texture, settings);
		CreateNew(mat, 1);
		return mat;
	}

	Material* MaterialFactory::Build(const String& name, const Color& color, const Shader* const shader, const String& sampler, const String& textureName, const RenderingSettings& settings)
	{
		return Build(name, color, shader, sampler, TextureFactory::Request2D(textureName), settings);
	}

	Material* MaterialFactory::Build(const String& name, const Color& color, const Shader* const shader, const RenderingSettings& settings)
	{
		Material* mat = new Material(name, color, shader, settings);
		CreateNew(mat, 1);
		return mat;
	}

	Material* MaterialFactory::Build(const String& name, const Color& color, const Shader* const shader, const TextureSet& textures, const RenderingSettings& settings)
	{
		Material* mat = new Material(name, color, shader, textures, settings);
		CreateNew(mat, 1);
		return mat;
	}

	PBRMaterial* MaterialFactory::BuildPBR(const String& name, const Color& color, const Shader* const shader, Texture* albedo, Texture* roughness, Texture* metallic, Texture* ao, Texture* normalMap,
		const RenderingSettings& settings)
	{
		PBRMaterial* mat = new PBRMaterial(name, color, shader, albedo, roughness, metallic, ao, normalMap, settings);
		CreateNew(mat, 1);
		return mat;
	}

	PBRMaterial* MaterialFactory::BuildPBR(const String& name, const Color& color, const Shader* const shader, const String& albedoTexture, const String& roughnessTexture, const String& metallicTexture, const String& aoTexture, const String& normalMap,
		const RenderingSettings& settings)
	{
		return BuildPBR(name, color, shader, TextureFactory::Request2D(albedoTexture), TextureFactory::Request2D(roughnessTexture), TextureFactory::Request2D(metallicTexture), TextureFactory::Request2D(aoTexture), TextureFactory::Request2D(normalMap), settings);
	}

	Material* MaterialFactory::BuildFont(const String& name, const Color& color, const Shader* const shader, const String& sampler, Font* font, const RenderingSettings& settings)
	{
		return Build(name, color, shader, sampler, font, settings);
	}

	Material* MaterialFactory::BuildFont(const String& name, const Color& color, const Shader* const shader, const String& sampler, const String& fontName, float size, const RenderingSettings& settings)
	{
		return BuildFont(name, color, shader, sampler, FontFactory::Request(fontName, size), settings);
	}

	void MaterialFactory::Order(const String& name, const Color& color, const Shader* const shader, const RenderingSettings& settings)
	{
		Decrement(Build(name, color, shader, settings)->GetName());
	}

	void MaterialFactory::Order(const String& name, const Color& color, const Shader* const shader, const String& sampler, Texture* texture, const RenderingSettings& settings)
	{
		Decrement(Build(name, color, shader, sampler, texture, settings)->GetName());
	}

	void MaterialFactory::Order(const String& name, const Color& color, const Shader* const shader, const String& sampler, const String& textureName, const RenderingSettings& settings)
	{
		Order(name, color, shader, sampler, TextureFactory::Request2D(textureName), settings);
	}

	void MaterialFactory::Order(const String& name, const Color& color, const Shader* const shader, const TextureSet& textures, const RenderingSettings& settings)
	{
		Decrement(Build(name, color, shader, textures, settings)->GetName());
	}

	void MaterialFactory::OrderPBR(const String& name, const Color& color, const Shader* const shader, Texture* albedo, Texture* roughness, Texture* metallic, Texture* ao, Texture* normalMap,
		const RenderingSettings& settings)
	{
		Decrement(BuildPBR(name, color, shader, albedo, roughness, metallic, ao, normalMap, settings)->GetName());
	}

	void MaterialFactory::OrderPBR(const String& name, const Color& color, const Shader* const shader, const String& albedoTexture, const String& roughnessTexture, const String& metallicTexture, const String& aoTexture, const String& normalMap,
		const RenderingSettings& settings)
	{
		OrderPBR(name, color, shader, TextureFactory::Request2D(albedoTexture), TextureFactory::Request2D(roughnessTexture), TextureFactory::Request2D(metallicTexture), TextureFactory::Request2D(aoTexture), TextureFactory::Request2D(normalMap), 
			settings);
	}

	void MaterialFactory::OrderFont(const String& name, const Color& color, const Shader* const shader, const String& sampler, Font* font, const RenderingSettings& settings)
	{
		Decrement(BuildFont(name, color, shader, sampler, font, settings)->GetName());
	}

	void MaterialFactory::OrderFont(const String& name, const Color& color, const Shader* const shader, const String& sampler, const String& fontName, float size, const RenderingSettings& settings)
	{
		Decrement(BuildFont(name, color, shader, sampler, fontName, size, settings)->GetName());
	}

	Material* MaterialFactory::Fabricate(const Color& color, const Shader* const shader, const RenderingSettings& settings)
	{
		String hashedName = "Material(" + std::to_string(color.r) + "," + std::to_string(color.g) + "," + std::to_string(color.b) + "," + std::to_string(color.a) + ")SHADER(" + shader->GetName() + ")SETTINGS(" + settings.ToString() + ")_HASHED_";
		if (ContainsKey(hashedName))
		{
			return Request(hashedName);
		}
		return Build(hashedName, color, shader, settings);
	}

	Material* MaterialFactory::Fabricate(const Color& color, const Shader* const shader, const String& sampler, const String& textureName, const RenderingSettings& settings)
	{
		String hashedName = "Material(" + std::to_string(color.r) + "," + std::to_string(color.g) + "," + std::to_string(color.b) + "," + std::to_string(color.a) + ")SHADER(" + shader->GetName() + ")TEXTURE(" + sampler + ", " + textureName + ")SETTINGS(" + settings.ToString() + ")_HASHED_";
		if (ContainsKey(hashedName))
		{
			return Request(hashedName);
		}
		return Build(hashedName, color, shader, sampler, textureName, settings);
	}

	Material* MaterialFactory::Fabricate(const Color& color, const Shader* const shader, const String& sampler, Texture* texture, const RenderingSettings& settings)
	{
		String hashedName = "";
		if (texture != nullptr)
			hashedName = "Material(" + std::to_string(color.r) + "," + std::to_string(color.g) + "," + std::to_string(color.b) + "," + std::to_string(color.a) + ")SHADER(" + shader->GetName() + ")TEXTURE(" + sampler + ", " + texture->GetName() + ")SETTINGS(" + settings.ToString() + ")_HASHED_";
		else
			hashedName = "Material(" + std::to_string(color.r) + "," + std::to_string(color.g) + "," + std::to_string(color.b) + "," + std::to_string(color.a) + ")SHADER(" + shader->GetName() + ")TEXTURE(" + sampler + ", " + "NULLPTR" + ")SETTINGS(" + settings.ToString() + ")_HASHED_";
		if (ContainsKey(hashedName))
		{
			return Request(hashedName);
		}
		return Build(hashedName, color, shader, sampler, texture, settings);
	}

	PBRMaterial* MaterialFactory::FabricatePBR(const Color& color, const Shader* const shader, const String& albedoTexture, const String& roughnessTexture, const String& metallicTexture, const String& aoTexture, const String& normalMap,
		const RenderingSettings& settings)
	{
		String hashedName = "PBRMaterial(" + std::to_string(color.r) + "," + std::to_string(color.g) + "," + std::to_string(color.b) + "," + std::to_string(color.a) + ")SHADER(" + shader->GetName() + ")TEXTURES(" + albedoTexture + ", " + roughnessTexture + ", " + metallicTexture + ", " + aoTexture + ", " + normalMap  + ")SETTINGS(" + settings.ToString() + ")_HASHED_";
		if (ContainsKey(hashedName))
		{
			return RequestPBR(hashedName);
		}
		return BuildPBR(hashedName, color, shader, albedoTexture, roughnessTexture, metallicTexture, aoTexture, normalMap, settings);
	}

	PBRMaterial* MaterialFactory::FabricatePBR(const Color& color, const Shader* const shader, Texture* albedo, Texture* roughness, Texture* metallic, Texture* ao, Texture* normalMap, 
		const RenderingSettings& settings)
	{
		return FabricatePBR(color, shader, albedo->GetName(), roughness->GetName(), metallic->GetName(), ao->GetName(), normalMap->GetName(), settings);
	}

	Material* MaterialFactory::FabricateFont(const Color& color, const Shader* const shader, const String& sampler, Font* font, const RenderingSettings& settings)
	{
		return Fabricate(color, shader, sampler, font, settings);
	}

	Material* MaterialFactory::FabricateFont(const Color& color, const Shader* const shader, const String& sampler, const String& fontName, float size, const RenderingSettings& settings)
	{
		return FabricateFont(color, shader, sampler, FontFactory::Request(fontName, size), settings);
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