#include "UniformManager.h"

namespace Ablaze
{

	UniformManager::UniformManager()
	{

	}

	void UniformManager::AddFloatUniform(const String& varname, float value)
	{
		floats[varname] = value;
	}

	void UniformManager::AddVec2Uniform(const String& varname, const maths::vec2& value)
	{
		vec2s[varname] = value;
	}

	void UniformManager::AddVec3Uniform(const String& varname, const maths::vec3& value)
	{
		vec3s[varname] = value;
	}

	void UniformManager::AddVec4Uniform(const String& varname, const maths::vec4& value)
	{
		vec4s[varname] = value;
	}

	void UniformManager::AddColorUniform(const String& varname, const Color& value)
	{
		colors[varname] = value;
	}

	void UniformManager::AddMat4Uniform(const String& varname, const maths::mat4& value)
	{
		mat4s[varname] = value;
	}

	float& UniformManager::GetFloat(const String& varname)
	{
		return floats[varname];
	}

	maths::vec2& UniformManager::GetVec2(const String& varname)
	{
		return vec2s[varname];
	}

	maths::vec3& UniformManager::GetVec3(const String& varname)
	{
		return vec3s[varname];
	}

	maths::vec4& UniformManager::GetVec4(const String& varname)
	{
		return vec4s[varname];
	}

	Color& UniformManager::GetColor(const String& varname)
	{
		return colors[varname];
	}

	maths::mat4& UniformManager::GetMat4(const String& varname)
	{
		return mat4s[varname];
	}

	void UniformManager::UploadAll(const Shader* const shader) const
	{
		shader->Enable();
		for (auto pair : floats)
		{
			shader->SetUniformFloat(pair.first, pair.second);
		}
		for (auto pair : vec2s)
		{
			shader->SetUniformVec2(pair.first, pair.second);
		}
		for (auto pair : vec3s)
		{
			shader->SetUniformVec3(pair.first, pair.second);
		}
		for (auto pair : vec4s)
		{
			shader->SetUniformVec4(pair.first, pair.second);
		}
		for (auto pair : colors)
		{
			shader->SetUniformColor(pair.first, pair.second);
		}
		for (auto pair : mat4s)
		{
			shader->SetUniformMat4(pair.first, pair.second);
		}
	}

	void UniformManager::UploadAll(const std::vector<Shader*>& shaders) const
	{
		for (auto shader : shaders)
		{
			UploadAll(shader);
		}
	}

	void UniformManager::ClearAll()
	{
		floats.clear();
		vec2s.clear();
		vec3s.clear();
		vec4s.clear();
		colors.clear();
		mat4s.clear();
	}

}