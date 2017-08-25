#pragma once
#include "Shader.h"

namespace Ablaze
{

	class ShaderManager
	{
	private:
		static const Shader* currentShader;
		static std::vector<Shader*> shaders;

		static void AddShader(Shader* shader);
		static void RemoveShader(Shader* shader);

	public:
		static void EnableShader(const Shader* shader);
		static void DisableShader(const Shader* shader);

		static const Shader* GetCurrentShader();
		static const std::vector<Shader*>& GetAllShaders();

		friend class Shader;

	};

}