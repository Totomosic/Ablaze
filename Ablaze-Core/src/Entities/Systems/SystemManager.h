#pragma once
#include "System.h"

namespace Ablaze
{

	class SystemManager
	{
	private:
		static std::vector<System*> systems;

	public:
		SystemManager() { }

		static void PushSystem(System* system);
		static System* PopSystem();

		static void Run();

	};

}