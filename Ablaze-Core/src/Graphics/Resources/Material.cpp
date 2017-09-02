#include "Material.h"

namespace Ablaze
{

	Material::Material(const String& name, const Color& color, const Shader* const shader, const TextureSet& textures, const RenderingSettings& settings) : Asset(name),
		diffuseColor(color), shader(shader), textures(textures), settings(settings)
	{

	}

	Material::Material(const String& name, const Color& color, const Shader* const shader, const String& sampler, Texture* texture, const RenderingSettings& settings) : Asset(name),
		diffuseColor(color), shader(shader), settings(settings)
	{
		textures.AddTexture(sampler, texture);
	}

	Material::Material(const String& name, const Color& color, const Shader* const shader, const RenderingSettings& settings) : Asset(name),
		diffuseColor(color), shader(shader), settings(settings)
	{
	
	}

	Material::Material() : Material::Material("", Color::White(), Shader::Default())
	{
		
	}

	Material::~Material()
	{
	
	}

	const Color& Material::GetColor() const
	{
		return diffuseColor;
	}

	const Shader* const Material::GetShader() const
	{
		return shader;
	}

	const RenderingSettings& Material::GetSettings() const
	{
		return settings;
	}

	Texture* Material::GetTexture(int index) const
	{
		return textures.textures[index]->second;
	}

	bool Material::HasTransparency() const
	{
		// TODO: make a lot more extensive to include transparency in model and textures
		return diffuseColor.a != 1.0f;
	}

	bool Material::HasTextures() const
	{
		return textures.textures.size() > 0;
	}

	UniformManager& Material::GetUniforms()
	{
		return uniforms;
	}

	void Material::AddTexture(const String& sampler, Texture* texture)
	{
		textures.AddTexture(sampler, texture);
	}

	const TextureSet& Material::GetAllTextures() const
	{
		return textures;
	}

	void Material::SetColor(const Color& color)
	{
		diffuseColor = color;
	}

	void Material::SetShader(const Shader* const shader)
	{
		this->shader = shader;
	}

	void Material::SetSettings(const RenderingSettings& settings)
	{
		this->settings = settings;
	}

	void Material::ApplyMaterial() const
	{
		shader->Enable();
		uniforms.UploadAll(*shader);
		shader->SetUniform("color", diffuseColor);
		settings.ApplySettings();
		int count = 0;
		for (auto texture : GetAllTextures().textures)
		{
			shader->SetTexture(*(texture->second), texture->first);
			count++;
		}
	}

}