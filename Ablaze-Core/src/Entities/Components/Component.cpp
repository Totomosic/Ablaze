#include "Component.h"

namespace Ablaze
{
	namespace Components
	{
		Component::Component()
		{
			owner = nullptr;
		}

		Component::~Component()
		{
			
		}

		void Component::SetOwner(const GameObject* owner)
		{
			this->owner = owner;
			Initialise();
		}

		const GameObject& Component::GetOwner() const
		{
			return *owner;
		}

		void Component::Initialise()
		{

		}
	}
}