#pragma once
#include "AblazeGL.h"
#include "Maths/Maths.h"
#include "structs/Data/Color.h"
#include "Utils/Utils.h"
#include "Graphics/Resources/Imaging/Textures/Texture.h"

namespace Ablaze
{

	class Shader
	{			
	private:
		static Shader* defaultShader;
		static Shader* textureShader;
		static Shader* fontShader;
		static Shader* pbrShader;
		static Shader* baseUIShader;

		String name;
		GLuint programID;
		String vertexString;
		String fragString;
		std::unordered_map<String, GLint>* uniformLocations;

	protected:
		Shader(const String& name, const String& vert, const String& frag);

	public:
		GLuint GetID() const;
		const String& GetName() const;

		void Enable() const;
		void Disable() const;

		void SetUniform(const String& varname, int value) const;
		void SetUniform(const String& varname, float value) const;
		void SetUniform(const String& varname, const maths::vec2& vec2) const;
		void SetUniform(const String& varname, const maths::vec3& vec3) const;
		void SetUniform(const String& varname, const maths::vec4& vec4) const;
		void SetUniform(const String& varname, const maths::mat4& matrix) const;
		void SetUniform(const String& varname, const Color& color) const;
		void SetUniform(const String& varname, const maths::Plane& plane) const;

		template<class T>
		void SetUniform(const String& varname, const T& value) const
		{
			SetUniform(varname, value);
		}

		void SetTexture(Ablaze::Texture& texture, const String& samplerName) const;

		static Shader* FromSource(const String& name, const String& vertexData, const String& fragData);
		static Shader* FromFile(const String& name, GLSLFile* vertexFile, GLSLFile* fragFile);
		static const Shader* const Default();
		static const Shader* const Texture();
		static const Shader* const Font();
		static const Shader* const PBR();
		static const Shader* const BaseUI();

	private:
		void Load(const String& vertex, const String& fragment);
		GLuint LoadShader(const String& shaderData, GLenum shaderType);
		GLint GetUniformLocation(const String& varname) const;
		static Shader* CreateDefault();
		static Shader* CreateTextureShader();
		static Shader* CreateFontShader();
		static Shader* CreatePBRShader();
		static Shader* CreateBaseUI();
		
	};

}