#include "Identifier.h"

namespace Ablaze
{
	namespace Components
	{

		Identifier::Identifier(const String& name)
			: name(name)
		{

		}

		Identifier::Identifier() : Identifier("Default")
		{

		}

		const String& Identifier::GetName() const
		{
			return name;
		}

		void Identifier::SetName(const String& name)
		{
			this->name = name;
		}

		Component* Identifier::Clone()
		{
			Identifier* id = new Identifier(name);
			return id;
		}

	}
}