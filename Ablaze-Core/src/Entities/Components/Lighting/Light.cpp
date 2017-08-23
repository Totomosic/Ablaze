#include "Light.h"

namespace Ablaze
{
	namespace Components
	{

		Light::Light(LightType type, const Color& color) : Component(), 
			type(type), color(color)
		{
		
		}

		LightType Light::GetType() const
		{
			return type;
		}

		const Color& Light::GetColor() const
		{
			return color;
		}

		void Light::SetType(LightType type)
		{
			this->type = type;
		}

		void Light::SetColor(const Color& color)
		{
			this->color = color;
		}

		Component* Light::Clone()
		{
			Light* l = new Light(type, color);
			return l;
		}

	}
}