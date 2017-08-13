#include "ComponentSet.h"
#include <iostream>

namespace Ablaze
{

	ComponentSet::ComponentSet(GameObject& owner) : owner(owner)
	{
		components = new std::unordered_map<std::type_index, Components::Component*>();
	}

	ComponentSet::~ComponentSet()
	{
		for (auto val : *components)
		{
			
			val.second;
		}
		delete components;
	}

	std::vector<Components::Component*> ComponentSet::GetAll() const
	{
		std::vector<Components::Component*> v;
		for (auto pair : *components)
		{
			v.push_back(pair.second);
		}
		return v;
	}

	void ComponentSet::AddComponent(Components::Component& component)
	{
		if (components->find(typeid(component)) != components->end())
		{
			// Type already exists
			delete (*components)[typeid(component)];
		}
		(*components)[typeid(component)] = &component;	
		component.SetOwner(&owner);
	}

	void ComponentSet::RemoveComponent(const std::type_index& componentType)
	{
		delete (*components)[componentType];
		components->erase(componentType);
	}

	bool ComponentSet::HasComponent(const std::type_index& componentType)
	{
		return components->find(componentType) != components->end();
	}

	Components::Component* ComponentSet::GetComponent(const std::type_index& componentType)
	{
		return (*components)[componentType];
	}

	void ComponentSet::RemoveAll()
	{
		for (auto pair : *components)
		{
			delete pair.second;
		}
		components->clear();
	}

}