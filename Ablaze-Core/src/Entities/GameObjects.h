#pragma once
#include <typeindex>
#include "Types.h"
#include "GameObject.h"

namespace Ablaze
{

	class GameObjects
	{
	public:
		GameObjects() { }

		static std::vector<GameObject*> GetAll();
		static std::vector<GameObject*> GetAllWith(const std::type_index* types, int length);
		static std::vector<GameObject*> GetAllWith(const std::type_index& type);

		template<class T> static std::vector<GameObject*> GetAllWith() { return GetAllWith(typeid(T)); }
		template<class T, class T1> static std::vector<GameObject*> GetAllWith() { return GetAllWith(new std::type_index[2]{ typeid(T), typeid(T1) }, 2); }
		template<class T, class T1, class T2> static std::vector<GameObject*> GetAllWith() { return GetAllWith(new std::type_index[3]{ typeid(T), typeid(T1), typeid(T2) }, 3); }
		template<class T, class T1, class T2, class T3> static std::vector<GameObject*> GetAllWith() { return GetAllWith(new std::type_index[4]{ typeid(T), typeid(T1), typeid(T2), typeid(T3) }, 4); }
		template<class T, class T1, class T2, class T3, class T4> static std::vector<GameObject*> GetAllWith() { return GetAllWith(new std::type_index[5]{ typeid(T), typeid(T1), typeid(T2), typeid(T3), typeid(T4) }, 5); }

		static std::vector<GameObject*> FindAllNearTo(const maths::vec3& position, float maxDistance);
		static std::vector<GameObject*> FindAllNearTo(const GameObject* const object, float maxDistance);
		static std::vector<GameObject*> FindAllNearTo(const Components::Transform* const transform, float maxDistance);
		static GameObject* FindNearestTo(const maths::vec3& position, float maxDistance);
		static GameObject* FindNearestTo(const GameObject* const object, float maxDistance);
		static GameObject* FindNearestTo(const Components::Transform* const transform, float maxDistance);

		static std::vector<GameObject*> GetAllWithName(const String& name);
		static GameObject* GetWithName(const String& name);

	};

}