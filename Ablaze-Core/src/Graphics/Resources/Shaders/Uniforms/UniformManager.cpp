#include "UniformManager.h"

namespace Ablaze
{

	UniformManager::UniformManager()
	{

	}

	void UniformManager::UploadAll(const Shader& shader) const
	{
		shader.Enable();
		for (int i = 0; i < uniforms.size(); i++)
		{
			uniforms[i]->UploadValue(shader);
		}
	}

	void UniformManager::UploadAll(const std::vector<Shader*>& shaders) const
	{
		for (auto shader : shaders)
		{
			UploadAll(*shader);
		}
	}

	void UniformManager::ClearAll()
	{
		uniforms.clear();
	}

}