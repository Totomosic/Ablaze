#pragma once
#include "Entities/Systems/System.h"

namespace Ablaze
{

	class LightingSystem : public System
	{
	public:
		LightingSystem();

		void Run() override;

	};

}