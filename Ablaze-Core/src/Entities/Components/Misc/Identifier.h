#pragma once
#include "../Component.h"

namespace Ablaze
{
	namespace Components
	{
		class Identifier : public Component
		{
		private:
			String name;

		public:
			Identifier(const String& name);
			Identifier();

			const String& GetName() const;
			void SetName(const String& name);

			Component* Clone() override;

		};
	}
}