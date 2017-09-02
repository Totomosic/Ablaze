#pragma once
#include "Uniform.h"

namespace Ablaze
{

	class UniformManager
	{
	private:
		std::vector<UniformRequest*> uniforms;

	public:
		UniformManager();

		template<class T>
		void AddUniform(const String& varname, const T& value)
		{
			Uniform<T>* uniform = new Uniform<T>(varname, value);
			uniforms.push_back(uniform);
		}

		template<class T>
		T& GetUniform(const String& varname)
		{
			for (auto uniform : uniforms)
			{
				Uniform<T>* realUniform = (Uniform<T>*)uniform;
				if (realUniform->GetVarname() == varname)
				{
					return realUniform->GetValue();
				}
			}
		}

		void UploadAll(const Shader& shader) const;
		void UploadAll(const std::vector<Shader*>& shaders) const;
		void ClearAll();

	};

}