#include "ShaderManager.h"

namespace Ablaze
{

	const Shader* ShaderManager::currentShader = nullptr;
	std::vector<Shader*> ShaderManager::shaders = std::vector<Shader*>();

	void ShaderManager::AddShader(Shader* shader)
	{
		shaders.push_back(shader);
	}

	void ShaderManager::RemoveShader(Shader* shader)
	{
		auto it = std::find(shaders.begin(), shaders.end(), shader);
		shaders.erase(it);
	}

	void ShaderManager::EnableShader(const Shader* shader)
	{
		currentShader = shader;
	}

	void ShaderManager::DisableShader(const Shader* shader)
	{
		currentShader = nullptr;
	}

	const Shader* ShaderManager::GetCurrentShader()
	{
		return currentShader;
	}

	const std::vector<Shader*>& ShaderManager::GetAllShaders()
	{
		return shaders;
	}

}