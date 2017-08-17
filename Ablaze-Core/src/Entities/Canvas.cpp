#include "Canvas.h"

namespace Ablaze
{

	Canvas::Canvas(const Window* const window, Origin originMode) : Canvas(maths::vec2(window->GetWidth(), window->GetHeight()), originMode)
	{
	
	}

	Canvas::Canvas(const maths::vec2& size, Origin originMode)
		: Camera((originMode == Origin::Center) ? Viewport(-size.x / 2.0f, -size.y / 2.0f, size.x, size.y) : (originMode == Origin::BottomLeft) ? Viewport(0, 0, size.x, size.y) : (originMode == Origin::TopRight) ? Viewport(size.x, size.y, -size.x, -size.y) : (originMode == Origin::BottomRight) ? Viewport(size.x, 0, -size.x, size.y) : Viewport(0, -size.y, size.x, size.y), maths::vec3(0, 0, 100), maths::mat4::Identity(), Projection::Orthographic)
	{
		
	}

}