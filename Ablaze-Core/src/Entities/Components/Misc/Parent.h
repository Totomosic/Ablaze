#pragma once
#include "../Component.h"

namespace Ablaze
{
	namespace Components
	{
		class Parent : public Component
		{
		private:
			const GameObject* const parent;

		public:
			Parent(const GameObject* const parent);
			Parent();

			const GameObject* const GetParentObject() const;

			Component* Clone() override;

		};
	}
}