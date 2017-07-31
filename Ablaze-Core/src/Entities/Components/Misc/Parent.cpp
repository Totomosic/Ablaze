#include "Parent.h"

namespace Ablaze
{
	namespace Components
	{
		Parent::Parent(const GameObject* const parent)
			: parent(parent)
		{
		
		}

		Parent::Parent() : Parent(nullptr)
		{

		}

		const GameObject* const Parent::GetParentObject() const
		{
			return parent;
		}

		Component* Parent::Clone()
		{
			Parent* p = new Parent(parent);
			return p;
		}
	}
}