#pragma once
#include "Types.h"
#include "Log.h"
#include "Factories/TextureFactory.h"
#include "structs/Data/Color.h"
#include "Graphics/Resources/Material.h"
#include "Graphics/Resources/PBRMaterial.h"

namespace Ablaze
{

	class MaterialFactory
	{
	private:
		static std::unordered_map<String, std::pair<Material*, int>*> materials;

	public:
		MaterialFactory() = delete;

		static Material* Request(const String& name);
		static Material* Request(const Material* const material);
		static PBRMaterial* RequestPBR(const String& name);
		static PBRMaterial* RequestPBR(const PBRMaterial* const material);
		static bool Release(const String& name);
		static bool Release(const Material* const material);
		static bool ReleasePBR(const String& name);
		static bool ReleasePBR(const PBRMaterial* const material);

		static Material* Build(const String& name, const Color& color, const Shader* const shader, const RenderingSettings& settings = RenderingSettings());
		static Material* Build(const String& name, const Color& color, const Shader* const shader, const String& sampler, Texture* texture, const RenderingSettings& settings = RenderingSettings());
		static Material* Build(const String& name, const Color& color, const Shader* const shader, const String& sampler, const String& textureName, const RenderingSettings& settings = RenderingSettings());
		static Material* Build(const String& name, const Color& color, const Shader* const shader, const TextureSet& textures, const RenderingSettings& settings = RenderingSettings());
		static PBRMaterial* BuildPBR(const String& name, const Color& color, const Shader* const shader, Texture* albedo, Texture* roughness, Texture* metallic, Texture* ao, Texture* normalMap,
			const RenderingSettings& settings = RenderingSettings());
		static PBRMaterial* BuildPBR(const String& name, const Color& color, const Shader* const shader, const String& albedoTexture, const String& roughnessTexture, const String& metallicTexture, const String& aoTexture, const String& normalMap,
			const RenderingSettings& settings = RenderingSettings());
		static Material* BuildFont(const String& name, const Color& color, const Shader* const shader, const String& sampler, Font* font, const RenderingSettings& settings = RenderingSettings());
		static Material* BuildFont(const String& name, const Color& color, const Shader* const shader, const String& sampler, const String& fontName, float size, const RenderingSettings& settings = RenderingSettings());

		static void Order(const String& name, const Color& color, const Shader* const shader, const RenderingSettings& settings = RenderingSettings());
		static void Order(const String& name, const Color& color, const Shader* const shader, const String& sampler, Texture* texture, const RenderingSettings& settings = RenderingSettings());
		static void Order(const String& name, const Color& color, const Shader* const shader, const String& sampler, const String& textureName, const RenderingSettings& settings = RenderingSettings());
		static void Order(const String& name, const Color& color, const Shader* const shader, const TextureSet& textures, const RenderingSettings& settings = RenderingSettings());
		static void OrderPBR(const String& name, const Color& color, const Shader* const shader, Texture* albedo, Texture* roughness, Texture* metallic, Texture* ao, Texture* normalMap, 
			const RenderingSettings& settings = RenderingSettings());
		static void OrderPBR(const String& name, const Color& color, const Shader* const shader, const String& albedoTexture, const String& roughnessTexture, const String& metallicTexture, const String& aoTexture, const String& normalMap,
			const RenderingSettings& settings = RenderingSettings());
		static void OrderFont(const String& name, const Color& color, const Shader* const shader, const String& sampler, Font* font, const RenderingSettings& settings = RenderingSettings());
		static void OrderFont(const String& name, const Color& color, const Shader* const shader, const String& sampler, const String& fontName, float size, const RenderingSettings& settings = RenderingSettings());

		static Material* Fabricate(const Color& color, const Shader* const shader, const RenderingSettings& settings = RenderingSettings());
		static Material* Fabricate(const Color& color, const Shader* const shader, const String& sampler, Texture* texture, const RenderingSettings& settings = RenderingSettings());
		static Material* Fabricate(const Color& color, const Shader* const shader, const String& sampler, const String& textureName, const RenderingSettings& settings = RenderingSettings());
		static PBRMaterial* FabricatePBR(const Color& color, const Shader* const shader, Texture* albedo, Texture* roughness, Texture* metallic, Texture* ao, Texture* normalMap,
			const RenderingSettings& settings = RenderingSettings());
		static PBRMaterial* FabricatePBR(const Color& color, const Shader* const shader, const String& albedoTexture, const String& roughnessTexture, const String& metallicTexture, const String& aoTexture, const String& normalMap,
			const RenderingSettings& settings = RenderingSettings());
		static Material* FabricateFont(const Color& color, const Shader* const shader, const String& sampler, Font* font, const RenderingSettings& settings = RenderingSettings());
		static Material* FabricateFont(const Color& color, const Shader* const shader, const String& sampler, const String& fontName, float size, const RenderingSettings& settings = RenderingSettings());

	private:
		static void Increment(const String& name);
		static void Decrement(const String& name);
		static void CreateNew(Material* material, int refCount);
		static bool ContainsKey(const String& name);

	};

}