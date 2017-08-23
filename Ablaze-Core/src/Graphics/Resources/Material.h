#pragma once
#include "Types.h"
#include "Resource.h"
#include "Graphics/Resources/Shaders/Shader.h"
#include "Graphics/Resources/Imaging/Textures/Texture.h"
#include "Graphics/Resources/Shaders/Uniforms/UniformManager.h"
#include "Graphics/Resources/Imaging/Textures/TextureSet.h"
#include "RenderingSettings.h"

namespace Ablaze
{

	class MaterialFactory;

	class Material : public Resource
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

		void AddTexture(const String& sampler, Texture* texture);
		const TextureSet& GetAllTextures() const;

		void AddUniformFloat(const String& varname, float value);
		void AddUniformVec2(const String& varname, const maths::vec2& value);
		void AddUniformVec3(const String& varname, const maths::vec3& value);
		void AddUniformVec4(const String& varname, const maths::vec4& value);
		void AddUniformColor(const String& varname, const Color& value);
		void AddUniformMat4(const String& varname, const maths::mat4& value);

		void SetColor(const Color& color);
		void SetShader(const Shader* const shader);
		void SetSettings(const RenderingSettings& settings);

		virtual void ApplyMaterial() const;

		friend class MaterialFactory;

	};

}