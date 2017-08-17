#pragma once
#include "Types.h"
#include "Log.h"
#include "Factories/TextureFactory.h"
#include "structs/Data/Color.h"
#include "Graphics/Resources/Material.h"
#include "RenderEngine/PBR/PBRMaterial.h"

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

		static Material* Build(const String& name, const Color& color, const Shader* const shader, const String& sampler, Texture* texture = nullptr, bool depth = true, bool blend = true, GLenum depthFunction = GL_LESS, GLenum blendSrcFunc = GL_SRC_ALPHA, GLenum blendDstFunc = GL_ONE_MINUS_SRC_ALPHA);
		static Material* Build(const String& name, const Color& color, const Shader* const shader, const String& sampler, const String& textureName, bool depth = true, bool blend = true, GLenum depthFunction = GL_LESS, GLenum blendSrcFunc = GL_SRC_ALPHA, GLenum blendDstFunc = GL_ONE_MINUS_SRC_ALPHA);
		static Material* Build(const String& name, const Color& color, const Shader* const shader, const TextureSet& textures, bool depth = true, bool blend = true, GLenum depthFunction = GL_LESS, GLenum blendSrcFunc = GL_SRC_ALPHA, GLenum blendDstFunc = GL_ONE_MINUS_SRC_ALPHA);
		static PBRMaterial* BuildPBR(const String& name, const Color& color, const Shader* const shader, Texture* albedo, Texture* roughness, Texture* metallic, Texture* ao, Texture* normalMap,
			bool depth = true, bool blend = true, GLenum depthFunction = GL_LESS, GLenum blendSrcFunc = GL_SRC_ALPHA, GLenum blendDstFunc = GL_ONE_MINUS_SRC_ALPHA);
		static PBRMaterial* BuildPBR(const String& name, const Color& color, const Shader* const shader, const String& albedoTexture, const String& roughnessTexture, const String& metallicTexture, const String& aoTexture, const String& normalMap,
			bool depth = true, bool blend = true, GLenum depthFunction = GL_LESS, GLenum blendSrcFunc = GL_SRC_ALPHA, GLenum blendDstFunc = GL_ONE_MINUS_SRC_ALPHA);
		static Material* BuildFont(const String& name, const Color& color, const Shader* const shader, const String& sampler, Font* font, bool depth = true, bool blend = true, GLenum depthFunction = GL_LEQUAL, GLenum blendSrcFunc = GL_SRC_ALPHA, GLenum blendDstFunc = GL_ONE_MINUS_SRC_ALPHA);
		static Material* BuildFont(const String& name, const Color& color, const Shader* const shader, const String& sampler, const String& fontName, float size, bool depth = true, bool blend = true, GLenum depthFunction = GL_LEQUAL, GLenum blendSrcFunc = GL_SRC_ALPHA, GLenum blendDstFunc = GL_ONE_MINUS_SRC_ALPHA);

		static void Order(const String& name, const Color& color, const Shader* const shader, const String& sampler, Texture* texture = nullptr, bool depth = true, bool blend = true, GLenum depthFunction = GL_LESS, GLenum blendSrcFunc = GL_SRC_ALPHA, GLenum blendDstFunc = GL_ONE_MINUS_SRC_ALPHA);
		static void Order(const String& name, const Color& color, const Shader* const shader, const String& sampler, const String& textureName, bool depth = true, bool blend = true, GLenum depthFunction = GL_LESS, GLenum blendSrcFunc = GL_SRC_ALPHA, GLenum blendDstFunc = GL_ONE_MINUS_SRC_ALPHA);
		static void Order(const String& name, const Color& color, const Shader* const shader, const TextureSet& textures, bool depth = true, bool blend = true, GLenum depthFunction = GL_LESS, GLenum blendSrcFunc = GL_SRC_ALPHA, GLenum blendDstFunc = GL_ONE_MINUS_SRC_ALPHA);
		static void OrderPBR(const String& name, const Color& color, const Shader* const shader, Texture* albedo, Texture* roughness, Texture* metallic, Texture* ao, Texture* normalMap, 
			bool depth = true, bool blend = true, GLenum depthFunction = GL_LESS, GLenum blendSrcFunc = GL_SRC_ALPHA, GLenum blendDstFunc = GL_ONE_MINUS_SRC_ALPHA);
		static void OrderPBR(const String& name, const Color& color, const Shader* const shader, const String& albedoTexture, const String& roughnessTexture, const String& metallicTexture, const String& aoTexture, const String& normalMap,
			bool depth = true, bool blend = true, GLenum depthFunction = GL_LESS, GLenum blendSrcFunc = GL_SRC_ALPHA, GLenum blendDstFunc = GL_ONE_MINUS_SRC_ALPHA);
		static void OrderFont(const String& name, const Color& color, const Shader* const shader, const String& sampler, Font* font, bool depth = true, bool blend = true, GLenum depthFunction = GL_LEQUAL, GLenum blendSrcFunc = GL_SRC_ALPHA, GLenum blendDstFunc = GL_ONE_MINUS_SRC_ALPHA);
		static void OrderFont(const String& name, const Color& color, const Shader* const shader, const String& sampler, const String& fontName, float size, bool depth = true, bool blend = true, GLenum depthFunction = GL_LEQUAL, GLenum blendSrcFunc = GL_SRC_ALPHA, GLenum blendDstFunc = GL_ONE_MINUS_SRC_ALPHA);

		static Material* Fabricate(const Color& color, const Shader* const shader, const String& sampler, Texture* texture = nullptr, bool depth = true, bool blend = true, GLenum depthFunction = GL_LESS, GLenum blendSrcFunc = GL_SRC_ALPHA, GLenum blendDstFunc = GL_ONE_MINUS_SRC_ALPHA);
		static Material* Fabricate(const Color& color, const Shader* const shader, const String& sampler, const String& textureName, bool depth = true, bool blend = true, GLenum depthFunction = GL_LESS, GLenum blendSrcFunc = GL_SRC_ALPHA, GLenum blendDstFunc = GL_ONE_MINUS_SRC_ALPHA);
		static PBRMaterial* FabricatePBR(const Color& color, const Shader* const shader, Texture* albedo, Texture* roughness, Texture* metallic, Texture* ao, Texture* normalMap,
			bool depth = true, bool blend = true, GLenum depthFunction = GL_LESS, GLenum blendSrcFunc = GL_SRC_ALPHA, GLenum blendDstFunc = GL_ONE_MINUS_SRC_ALPHA);
		static PBRMaterial* FabricatePBR(const Color& color, const Shader* const shader, const String& albedoTexture, const String& roughnessTexture, const String& metallicTexture, const String& aoTexture, const String& normalMap,
			bool depth = true, bool blend = true, GLenum depthFunction = GL_LESS, GLenum blendSrcFunc = GL_SRC_ALPHA, GLenum blendDstFunc = GL_ONE_MINUS_SRC_ALPHA);
		static Material* FabricateFont(const Color& color, const Shader* const shader, const String& sampler, Font* font, bool depth = true, bool blend = true, GLenum depthFunction = GL_LEQUAL, GLenum blendSrcFunc = GL_SRC_ALPHA, GLenum blendDstFunc = GL_ONE_MINUS_SRC_ALPHA);
		static Material* FabricateFont(const Color& color, const Shader* const shader, const String& sampler, const String& fontName, float size, bool depth = true, bool blend = true, GLenum depthFunction = GL_LEQUAL, GLenum blendSrcFunc = GL_SRC_ALPHA, GLenum blendDstFunc = GL_ONE_MINUS_SRC_ALPHA);

	private:
		static void Increment(const String& name);
		static void Decrement(const String& name);
		static void CreateNew(Material* material, int refCount);
		static bool ContainsKey(const String& name);

	};

}