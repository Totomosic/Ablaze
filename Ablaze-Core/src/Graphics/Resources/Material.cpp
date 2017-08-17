#include "Material.h"

namespace Ablaze
{

	Material::Material(const String& name, const Color& color, const Shader* const shader, const TextureSet& textures, bool depthState, bool blendState, GLenum depthFunction, GLenum srcBlendState, GLenum dstBlendState) : Resource(name), 
		diffuseColor(color), shader(shader), textures(textures), depthState(depthState), blendState(blendState), depthFunction(depthFunction), srcBlendState(srcBlendState), dstBlendState(dstBlendState)
	{

	}

	Material::Material(const String& name, const Color& color, const Shader* const shader, const String& sampler, Texture* texture, bool depthState, bool blendState, GLenum depthFunction, GLenum srcBlendState, GLenum dstBlendState) : Resource(name), 
		diffuseColor(color), shader(shader), depthState(depthState), blendState(blendState), depthFunction(depthFunction), srcBlendState(srcBlendState), dstBlendState(dstBlendState)
	{
		if (texture != nullptr)
		{
			textures.AddTexture(sampler, texture);
		}
		else
		{
			AB_WARN("Texture was nullptr");
		}
	}

	Material::Material() : Material::Material("", Color::White(), nullptr, "", nullptr, true, true, GL_LESS, GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA)
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

	Texture* Material::GetTexture(int index) const
	{
		return textures.textures[index]->second;
	}

	bool Material::GetDepthState() const
	{
		return depthState;
	}

	bool Material::GetBlendState() const
	{
		return blendState;
	}

	GLenum Material::GetDepthFunc() const
	{
		return depthFunction; 
	}

	GLenum Material::GetSrcBlend() const
	{
		return srcBlendState;
	}

	GLenum Material::GetDstBlend() const
	{
		return dstBlendState;
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

	void Material::SetDepthState(bool depth)
	{
		depthState = depth;
	}

	void Material::SetBlendState(bool blend)
	{
		blendState = blend;
	}

	void Material::SetDepthFunc(GLenum func)
	{
		depthFunction = func;
	}

	void Material::SetSrcBlend(GLenum src)
	{
		srcBlendState = src;
	}

	void Material::SetDstBlend(GLenum dst)
	{
		dstBlendState = dst;
	}

	void Material::ApplyMaterial() const
	{
		shader->Enable();
		uniforms.UploadAll(shader);
		if (depthState)
		{
			glEnable(GL_DEPTH_TEST);
			glDepthFunc(depthFunction);
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
		int count = 0;
		for (auto texture : GetAllTextures().textures)
		{
			shader->SetTexture(*(texture->second), texture->first);
			count++;
		}
	}

}