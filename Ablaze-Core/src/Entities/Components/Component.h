#pragma once
#include "Enums.h"
#include "Maths/Maths.h"
#include "Types.h"

namespace Ablaze
{
	class GameObject;

	namespace Components
	{
		class Component
		{
		protected:
			const GameObject* owner;

		public:
			Component();
			virtual ~Component();

			virtual Component* Clone() = 0;

			void SetOwner(const GameObject* owner);
			const GameObject& GetOwner() const;

			// Function that is called every time the owner is set
			virtual void Initialise();

		};
	}
}