#pragma once
#include "Enums.h"
#include "Types.h"
#include "Entities/Components/Component.h"

namespace Ablaze
{
	namespace Components
	{

		class Light : public Component
		{
		private:
			LightType type;
			Color color;

		public:
			Light(LightType type = LightType::Point, const Color& color = Color::White());

			LightType GetType() const;
			const Color& GetColor() const;

			void SetType(LightType type);
			void SetColor(const Color& color);

			Component* Clone() override;

		};

	}
}