#include "GameObjects.h"
#include "Components/Misc/Identifier.h"
#include "Components/Motion/Transform.h"

namespace Ablaze
{

	std::vector<GameObject*> GameObjects::GetAll()
	{
		std::vector<GameObject*> v;
		for (int i = 0; i < GameObject::GetHightestID() + 1; i++)
		{
			if (GameObject::IsValid(i))
			{
				v.push_back(GameObject::GetAtID(i));
			}
		}
		return v;
	}

	std::vector<GameObject*> GameObjects::GetAllWith(const std::type_index* types, int length)
	{
		std::vector<GameObject*> v;
		for (int i = 0; i < GameObject::GetHightestID() + 1; i++)
		{
			if (!GameObject::IsValid(i))
			{
				// If current GameObject is not valid, move on to the next
				continue;
			}
			GameObject* g = GameObject::GetAtID(i);
			bool passed = true;
			for (int j = 0; j < length; j++)
			{
				if (!g->GetComponentSet().HasComponent(types[j]))
				{
					// If object doesn't have a specific component then move on to the next one
					passed = false;
					break;
				}
			}
			// If all tests pass, add it to vector
			if (passed)
			{
				v.push_back(GameObject::GetAtID(i));
			}
		}
		// Delete array pointer
		delete[] types;
		return v;
	}

	std::vector<GameObject*> GameObjects::GetAllWith(const std::type_index& type)
	{
		return GetAllWith(new std::type_index[1]{ type }, 1);
	}

	std::vector<GameObject*> GameObjects::FindAllNearTo(const maths::vec3& position, float maxDistance)
	{
		std::vector<GameObject*> objects;
		for (uint i = 1; i < GameObject::GetHightestID() + 1; i++)
		{
			if (!GameObject::IsValid(i))
			{
				continue;
			}
			GameObject* object = GameObject::GetAtID(i);
			Components::Transform* transform = nullptr;
			if (object->GetComponentSet().GetComponent(transform))
			{
				if (maths::vec3::Distance(position, transform->GetPosition()) <= maxDistance)
				{
					objects.push_back(object);
				}
			}
		}
		return objects;
	}

	std::vector<GameObject*> GameObjects::FindAllNearTo(const GameObject* const object, float maxDistance)
	{
		return FindAllNearTo(object->Transform(), maxDistance);
	}

	std::vector<GameObject*> GameObjects::FindAllNearTo(const Components::Transform* const transform, float maxDistance)
	{
		std::vector<GameObject*> objects;
		for (uint i = 1; i < GameObject::GetHightestID() + 1; i++)
		{
			if (i == transform->GetOwner().GetID() || !GameObject::IsValid(i))
			{
				continue;
			}
			GameObject* object = GameObject::GetAtID(i);
			Components::Transform* transform = nullptr;
			if (object->GetComponentSet().GetComponent(transform))
			{
				if (maths::vec3::Distance(object->Transform()->GetPosition(), transform->GetPosition()) <= maxDistance)
				{
					objects.push_back(object);
				}
			}
		}
		return objects;
	}

	GameObject* GameObjects::FindNearestTo(const maths::vec3& position, float maxDistance)
	{
		GameObject* obj = nullptr;
		float dist = maxDistance + 1;
		for (uint i = 1; i < GameObject::GetHightestID() + 1; i++)
		{
			if (!GameObject::IsValid(i))
			{
				continue;
			}
			GameObject* object = GameObject::GetAtID(i);
			Components::Transform* transform = nullptr;
			if (object->GetComponentSet().GetComponent(transform))
			{
				float distance = maths::vec3::Distance(position, transform->GetPosition());
				if (distance < dist && distance <= maxDistance)
				{
					obj = object;
					dist = distance;
				}
			}
		}
		return obj;
	}

	GameObject* GameObjects::FindNearestTo(const GameObject* const object, float maxDistance)
	{
		return FindNearestTo(object->Transform(), maxDistance);
	}

	GameObject* GameObjects::FindNearestTo(const Components::Transform* const transform, float maxDistance)
	{
		GameObject* obj = nullptr;
		float dist = maxDistance + 1;
		// Start at 1 to ignore anchor
		for (uint i = 1; i < GameObject::GetHightestID() + 1; i++)
		{
			if (i == transform->GetOwner().GetID() && !GameObject::IsValid(i))
			{
				continue;
			}
			GameObject* object = GameObject::GetAtID(i);
			Components::Transform* transform = nullptr;
			if (object->GetComponentSet().GetComponent(transform))
			{
				float distance = maths::vec3::Distance(transform->GetPosition(), transform->GetPosition());
				if (distance < dist && distance <= maxDistance)
				{
					obj = object;
					dist = distance;
				}
			}
		}
		return obj;
	}

	std::vector<GameObject*> GameObjects::GetAllWithName(const String& name)
	{
		std::vector<GameObject*> v;
		for (int i = 0; i < GameObject::GetHightestID() + 1; i++)
		{
			if (!GameObject::IsValid(i))
			{
				continue;
			}
			GameObject* obj = GameObject::GetAtID(i);
			if (!obj->HasComponent<Components::Identifier>())
			{
				continue;
			}
			if (obj->GetComponent<Components::Identifier>()->GetName() == name)
			{
				v.push_back(obj);
			}
		}
		return v;
	}

	GameObject* GameObjects::GetWithName(const String& name)
	{
		for (int i = 0; i < GameObject::GetHightestID() + 1; i++)
		{
			if (!GameObject::IsValid(i))
			{
				continue;
			}
			GameObject* obj = GameObject::GetAtID(i);
			if (obj->HasComponent<Components::Identifier>())
			{
				if (obj->GetComponent<Components::Identifier>()->GetName() == name)
				{
					return obj;
				}
			}
		}
		return nullptr;
	}

}