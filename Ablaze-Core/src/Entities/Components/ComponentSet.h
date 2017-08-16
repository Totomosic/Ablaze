#pragma once
#include <vector>
#include <map>
#include <typeindex>
#include <typeinfo>

#include "Component.h"

namespace Ablaze
{

	namespace Components
	{
		class Transform;
	}

	class ComponentSet
	{
	private:
		GameObject& owner;
		std::unordered_map<std::type_index, Components::Component*>* components;

	public:
		ComponentSet(GameObject& owner);
		~ComponentSet();

		std::vector<Components::Component*> GetAll() const;
		void AddComponent(Components::Component& component);
		void RemoveAll();
		void RemoveComponent(const std::type_index& componentType);

		bool HasComponent(const std::type_index& componentType);
		Components::Component* GetComponent(const std::type_index& componentType);

		template<class T> bool GetComponent(T* outComponent)
		{
			if (HasComponent<T>())
			{
				T* component = GetComponent<T>();
				outComponent = component;
				return true;
			}
			return false;
		}

		template<class T> T* GetComponent()
		{
			return (T*)GetComponent(typeid(T));
		}

		template<class T> void RemoveComponent()
		{
			RemoveComponent(typeid(T));
		}

		template<class T> bool HasComponent()
		{
			return HasComponent(typeid(T));
		}

	};

}