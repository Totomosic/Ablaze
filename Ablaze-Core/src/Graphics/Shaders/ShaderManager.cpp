#include "ShaderManager.h"

namespace Ablaze
{

	const Shader* ShaderManager::currentShader = nullptr;

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

}