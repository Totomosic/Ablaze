#pragma once
#include "Entities/Systems/System.h"
#include "Graphics/Resources/Shaders/ShaderManager.h"

namespace Ablaze
{

	class LightingSystem : public System
	{
	public:
		LightingSystem();

		void Run() override;

	};

}