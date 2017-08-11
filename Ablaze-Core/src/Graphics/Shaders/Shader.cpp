#include "Shader.h"
#include "ShaderManager.h"
#include "Log.h"

namespace Ablaze
{

	Shader* Shader::defaultShader = nullptr;
	Shader* Shader::textureShader = nullptr;
	Shader* Shader::fontShader = nullptr;
	Shader* Shader::pbrShader = nullptr;

	Shader::Shader(const String& name, const String& vertex, const String& frag)
		: name(name), vertexString(&vertex), fragString(&frag)
	{
		this->uniformLocations = new std::unordered_map<String, GLint>();
		Load(vertex, frag);
	}

	GLuint Shader::GetID() const
	{
		return programID;
	}

	const String& Shader::GetName() const
	{
		return name;
	}

	void Shader::Enable() const
	{
		if (ShaderManager::GetCurrentShader() != this)
		{
			glUseProgram(programID);
			ShaderManager::EnableShader(this);
		}
	}

	void Shader::Disable() const
	{
		glUseProgram(0);
		ShaderManager::DisableShader(this);
	}

	void Shader::SetUniformInt(String varname, int value) const
	{
		glUniform1i(GetUniformLocation(varname), value);
	}

	void Shader::SetUniformFloat(String varname, float value) const
	{
		glUniform1f(GetUniformLocation(varname), value);
	}

	void Shader::SetUniformVec2(String varname, const maths::vec2& vec2) const
	{
		glUniform2f(GetUniformLocation(varname), vec2.x, vec2.y);
	}

	void Shader::SetUniformVec3(String varname, const maths::vec3& vec3) const
	{
		glUniform3f(GetUniformLocation(varname), vec3.x, vec3.y, vec3.z);
	}

	void Shader::SetUniformVec4(String varname, const maths::vec4& vec4) const
	{
		glUniform4f(GetUniformLocation(varname), vec4.x, vec4.y, vec4.z, vec4.z);
	}

	void Shader::SetUniformMat4(String varname, const maths::mat4& mat4) const
	{
		glUniformMatrix4fv(GetUniformLocation(varname), 1, GL_FALSE, mat4.values);
	}

	void Shader::SetUniformColor(String varname, const Color& color) const
	{
		glUniform4f(GetUniformLocation(varname), color.r, color.g, color.b, color.a);
	}

	void Shader::SetTexture(Ablaze::Texture& texture, String textureBank) const
	{
		int bank = texture.GetBindUnit();
		if (bank == -1)
		{
			bank = texture.Bind();
		}
		SetUniformInt(textureBank, bank);
	}

	Shader* Shader::FromSource(const String& name, const String& vertexData, const String& fragData)
	{
		return new Shader(name, vertexData, fragData);
	}

	Shader* Shader::FromFile(const String& name, GLSLFile* vertexFile, GLSLFile* fragFile)
	{
		vertexFile->Open(OpenMode::Read);
		fragFile->Open(OpenMode::Read);
		Shader* shader = new Shader(name, vertexFile->Read(), fragFile->Read());
		vertexFile->Close();
		fragFile->Close();
		return shader;
	}

	const Shader* const Shader::Default()
	{
		if (defaultShader == nullptr)
		{
			defaultShader = CreateDefault();
		}
		return defaultShader;
	}

	const Shader* const Shader::Texture()
	{
		if (textureShader == nullptr)
		{
			textureShader = CreateTextureShader();
		}
		return textureShader;
	}

	const Shader* const Shader::Font()
	{
		if (fontShader == nullptr)
		{
			fontShader = CreateFontShader();
		}
		return fontShader;
	}

	const Shader* const Shader::PBR()
	{
		if (pbrShader == nullptr)
		{
			pbrShader = CreatePBRShader();
		}
		return pbrShader;
	}

	void Shader::Load(const String& v, const String& f)
	{
		GLuint id = glCreateProgram();
		programID = id;
		GLuint vertex = LoadShader(v, GL_VERTEX_SHADER);
		GLuint fragment = LoadShader(f, GL_FRAGMENT_SHADER);
		glLinkProgram(programID);
		glValidateProgram(programID);

		GLint status;
		glGetProgramiv(programID, GL_LINK_STATUS, &status);
		if (status == 0)
		{
			std::cout << "Link Error" << std::endl;
		}

		glDeleteShader(vertex);
		glDeleteShader(fragment);
	}

	GLuint Shader::LoadShader(const String& shaderData, GLenum shaderType)
	{		
		GLuint shaderID = glCreateShader(shaderType);

		const char* source = shaderData.c_str();

		glShaderSource(shaderID, 1, &source, nullptr);
		glCompileShader(shaderID);
		
		GLint result;
		glGetShaderiv(shaderID, GL_COMPILE_STATUS, &result);
		if (result == GL_FALSE)
		{
			GLint length;
			glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &length);
			std::vector<char> error(length);
			glGetShaderInfoLog(shaderID, length, &length, &error[0]);
			String errorMessage(&error[0]);
			glDeleteShader(shaderID);
			AB_ERROR(errorMessage);
			return 0;
		}

		glAttachShader(programID, shaderID);
		return shaderID;
	}

	GLint Shader::GetUniformLocation(String varname) const
	{
		if (uniformLocations->find(varname) == uniformLocations->end())
		{
			// not found
			GLint location = glGetUniformLocation(programID, varname.c_str());
			(*uniformLocations)[varname] = location;

			if (location == -1)
			{
				AB_WARN(std::string("Shader variable not found: ") + std::string(varname));
			}

			return location;
		}
		else
		{
			// found
			return (*uniformLocations)[varname];
		}
	}

	Shader* Shader::CreateDefault()
	{
		String vData =
#include "Source/base_v.glsl"
			;

		String fData =
#include "Source/base_f.glsl"
			;

		return Shader::FromSource("_Default", vData, fData);
	}

	Shader* Shader::CreateFontShader()
	{
		String vData =
#include "Source/font_v.glsl"
			;
		String fData =
#include "Source/font_f.glsl"
			;

		return Shader::FromSource("_Font", vData, fData);
	}

	Shader* Shader::CreatePBRShader()
	{
		String vData =
#include "Source/pbr_v.glsl"
			;
		String fData =
#include "Source/pbr_f.glsl"
			;
		
		return Shader::FromSource("_PBR", vData, fData);
	}

	Shader* Shader::CreateTextureShader()
	{
		String vData =
#include "Source/texture_v.glsl"
			;
		String fData =
#include "Source/texture_f.glsl"
			;

		return Shader::FromSource("_Texture", vData, fData);
	}

}