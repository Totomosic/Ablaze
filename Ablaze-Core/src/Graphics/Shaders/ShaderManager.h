#pragma once
#include "Shader.h"

namespace Ablaze
{

	class ShaderManager
	{
	private:
		static const Shader* currentShader;

	public:
		static void EnableShader(const Shader* shader);
		static void DisableShader(const Shader* shader);

		static const Shader* GetCurrentShader();

	};

}