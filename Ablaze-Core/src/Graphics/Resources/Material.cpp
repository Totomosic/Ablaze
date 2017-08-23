#include "Material.h"

namespace Ablaze
{

	Material::Material(const String& name, const Color& color, const Shader* const shader, const TextureSet& textures, const RenderingSettings& settings) : Resource(name),
		diffuseColor(color), shader(shader), textures(textures), settings(settings)
	{

	}

	Material::Material(const String& name, const Color& color, const Shader* const shader, const String& sampler, Texture* texture, const RenderingSettings& settings) : Resource(name),
		diffuseColor(color), shader(shader), settings(settings)
	{
		textures.AddTexture(sampler, texture);
	}

	Material::Material(const String& name, const Color& color, const Shader* const shader, const RenderingSettings& settings) : Resource(name),
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

	void Material::AddTexture(const String& sampler, Texture* texture)
	{
		textures.AddTexture(sampler, texture);
	}

	const TextureSet& Material::GetAllTextures() const
	{
		return textures;
	}

	void Material::AddUniformFloat(const String& varname, float value)
	{
		uniforms.AddFloatUniform(varname, value);
	}

	void Material::AddUniformVec2(const String& varname, const maths::vec2& value)
	{
		uniforms.AddVec2Uniform(varname, value);
	}

	void Material::AddUniformVec3(const String& varname, const maths::vec3& value)
	{
		uniforms.AddVec3Uniform(varname, value);
	}

	void Material::AddUniformVec4(const String& varname, const maths::vec4& value)
	{
		uniforms.AddVec4Uniform(varname, value);
	}

	void Material::AddUniformColor(const String& varname, const Color& value)
	{
		uniforms.AddColorUniform(varname, value);
	}

	void Material::AddUniformMat4(const String& varname, const maths::mat4& value)
	{
		uniforms.AddMat4Uniform(varname, value);
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
		uniforms.UploadAll(shader);
		settings.ApplySettings();
		int count = 0;
		for (auto texture : GetAllTextures().textures)
		{
			shader->SetTexture(*(texture->second), texture->first);
			count++;
		}
	}

}