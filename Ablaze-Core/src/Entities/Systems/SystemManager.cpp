#include "SystemManager.h"

namespace Ablaze
{

	std::vector<System*> SystemManager::systems = std::vector<System*>();

	void SystemManager::PushSystem(System* system)
	{
		systems.push_back(system);
	}

	System* SystemManager::PopSystem()
	{
		System* s = systems.back();
		systems.pop_back();
		return s;
	}

	void SystemManager::Run()
	{
		for (int i = systems.size() - 1; i >= 0; i--)
		{
			systems[i]->Run();
		}
	}

}