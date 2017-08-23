#include "Component.h"

namespace Ablaze
{
	namespace Components
	{
		Component::Component()
		{
			owner = nullptr;
			isActive = true;
		}

		Component::~Component()
		{
			
		}

		const GameObject& Component::GetOwner() const
		{
			return *owner;
		}

		bool Component::IsActive() const
		{
			return isActive;
		}

		void Component::SetOwner(GameObject* owner)
		{
			this->owner = owner;
			Initialise();
		}

		void Component::Enable()
		{
			SetActive(true);
		}

		void Component::Disable()
		{
			SetActive(false);
		}

		void Component::SetActive(bool isActive)
		{
			this->isActive = isActive;
		}

		void Component::Initialise()
		{

		}
	}
}