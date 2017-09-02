#pragma once
#include "Types.h"
#include "Asset.h"
#include "Graphics/Resources/Shaders/Shader.h"
#include "Graphics/Resources/Imaging/Textures/Texture.h"
#include "Graphics/Resources/Shaders/Uniforms/UniformManager.h"
#include "Graphics/Resources/Imaging/Textures/TextureSet.h"
#include "RenderingSettings.h"

namespace Ablaze
{

	class MaterialFactory;

	class Material : public Asset
	{
	protected:
		Color diffuseColor;
		const Shader* shader;
		RenderingSettings settings;
		TextureSet textures;
		UniformManager uniforms;

	protected:
		Material(const String& name, const Color& color, const Shader* const shader, const TextureSet& textures, const RenderingSettings& settings = RenderingSettings());
		Material(const String& name, const Color& color, const Shader* const shader, const String& sampler, Texture* texture, const RenderingSettings& settings = RenderingSettings());
		Material(const String& name, const Color& color, const Shader* const shader, const RenderingSettings& settings = RenderingSettings());
		Material();

	public:
		~Material() override;

		const Color& GetColor() const;
		const Shader* const GetShader() const;
		const RenderingSettings& GetSettings() const;
		Texture* GetTexture(int index = 0) const;
		bool HasTransparency() const;
		bool HasTextures() const;
		UniformManager& GetUniforms();

		void AddTexture(const String& sampler, Texture* texture);
		const TextureSet& GetAllTextures() const;

		template<class T>
		void AddUniform(const String& varname, const T& value)
		{
			uniforms.AddUniform<T>(varname, value);
		}

		void SetColor(const Color& color);
		void SetShader(const Shader* const shader);
		void SetSettings(const RenderingSettings& settings);

		virtual void ApplyMaterial() const;

		friend class MaterialFactory;

	};

}