#include "Widget.h"
#include "Entities/Components/Components.h"

namespace Ablaze
{

	Widget::Widget(const maths::vec3& position, const maths::vec2& size, const maths::mat4& rotation, const maths::vec3& scale) : GameObject(position, rotation, scale),
		size(size)
	{
		AddComponent(new Components::Collider(OBB(maths::vec3(size, 100))));
	}

	Widget::Widget(float x, float y, float z, const maths::vec2& size, const maths::mat4& rotation, const maths::vec3& scale) : Widget(maths::vec3(x, y, z), size, rotation, scale)
	{
	
	}

	Widget::Widget(const maths::vec2& size) : Widget(0, 0, 0, size)
	{
	
	}

	maths::vec3 Widget::Position() const
	{
		return Transform()->GetPosition();
	}

	const maths::vec2& Widget::Size() const
	{
		return size;
	}

}