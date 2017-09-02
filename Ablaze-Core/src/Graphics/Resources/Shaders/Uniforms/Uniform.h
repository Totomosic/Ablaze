#pragma once
#include "Graphics/Resources/Shaders/Shader.h"
#include "Object.h"

namespace Ablaze
{

	class UniformRequest : public Object
	{
	public:
		virtual void UploadValue(const Shader& shader) const = 0;
		virtual const String& GetVarname() const = 0;

	};

	template<class T>
	class Uniform : public UniformRequest
	{
	private:
		T value;
		String varname;

	public:
		Uniform(const String& varname, const T& value)
			: value(value), varname(varname)
		{
		
		}

		const T& GetValue() const { return value; }
		T& GetValue() { return value; }
		const String& GetVarname() const override { return varname; }
		void SetVarname(const String& varname) { this->varname = varname; }

		void SetValue(const T& value) { this->value = value; }

		void UploadValue(const Shader& shader) const override
		{
			shader.SetUniform<T>(varname, value);
		}

		String ToString() const override
		{
			return "Uniform Request: " + varname;
		}

	};

}