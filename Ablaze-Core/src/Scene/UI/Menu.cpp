#include "Menu.h"

namespace Ablaze
{

	Menu::Menu(const maths::vec3& position, const maths::vec2& size, const Color& color, const maths::mat4& transform) : Panel(position, size, color, transform)
	{
	
	}

	Menu::Menu(const maths::vec3& position, float w, float h, const Color& color, const maths::mat4& transform) : Menu(position, maths::vec2(w, h), color, transform)
	{
	
	}

	Menu::Menu(float x, float y, float z, const maths::vec2& size, const Color& color, const maths::mat4& transform) : Menu(maths::vec3(x, y, z), size, color, transform)
	{
	
	}	

	Menu::Menu(float x, float y, float z, float w, float h, const Color& color, const maths::mat4& transform) : Menu(x, y, z, maths::vec2(w, h), color, transform)
	{
	
	}

	Menu::Menu(float x, float y, const maths::vec2& size, const Color& color, const maths::mat4& transform) : Menu(maths::vec3(x, y, 0), size, color, transform)
	{
	
	}

	Menu::Menu(float x, float y, float w, float h, const Color& color, const maths::mat4& transform) : Menu(x, y, maths::vec2(w, h), color, transform)
	{
	
	}	

	GameObject* Menu::GetWidget(int index) const
	{
		return widgets[index];
	}

	void Menu::PushWidget(GameObject* widget)
	{
		widgets.push_back(widget);
	}

}