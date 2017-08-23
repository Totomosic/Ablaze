#pragma once
#include "Enums.h"
#include "Types.h"

namespace Ablaze
{
	class GameObject;

	namespace Components
	{
		class Component
		{
		protected:
			GameObject* owner;
			bool isActive;

		public:
			Component();
			virtual ~Component();

			virtual Component* Clone() = 0;

			const GameObject& GetOwner() const;
			bool IsActive() const;
			void SetOwner(GameObject* owner);
			void Enable();
			void Disable();
			void SetActive(bool isActive);

			// Function that is called every time the owner is set
			virtual void Initialise();

		};
	}
}