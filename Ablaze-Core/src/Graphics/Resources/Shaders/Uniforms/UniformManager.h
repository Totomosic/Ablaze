#pragma once
#include "Graphics/Resources/Shaders/Shader.h"
#include "Maths/Maths.h"
#include "Types.h"

namespace Ablaze
{

	class UniformManager
	{
	private:
		std::unordered_map<String, float> floats;
		std::unordered_map<String, maths::vec2> vec2s;
		std::unordered_map<String, maths::vec3> vec3s;
		std::unordered_map<String, maths::vec4> vec4s;
		std::unordered_map<String, Color> colors;
		std::unordered_map<String, maths::mat4> mat4s;

	public:
		UniformManager();

		void AddFloatUniform(const String& varname, float value);
		void AddVec2Uniform(const String& varname, const maths::vec2& value);
		void AddVec3Uniform(const String& varname, const maths::vec3& value);
		void AddVec4Uniform(const String& varname, const maths::vec4& value);
		void AddColorUniform(const String& varname, const Color& value);
		void AddMat4Uniform(const String& varname, const maths::mat4& value);

		float& GetFloat(const String& varname);
		maths::vec2& GetVec2(const String& varname);
		maths::vec3& GetVec3(const String& varname);
		maths::vec4& GetVec4(const String& varname);
		Color& GetColor(const String& varname);
		maths::mat4& GetMat4(const String& varname);

		void UploadAll(const Shader* const shader) const;
		void UploadAll(const std::vector<Shader*>& shaders) const;
		void ClearAll();

	};

}