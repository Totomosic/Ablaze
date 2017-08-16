#pragma once
#include "Camera.h"
#include "Graphics/Window.h"

namespace Ablaze
{

	enum class Origin
	{
		Center, TopLeft, BottomLeft, TopRight, BottomRight
	};

	class Canvas : public Camera
	{
	public:
		Canvas(const Window* const window, Origin originMode);
		Canvas(const maths::vec2& size, Origin originMode);
	};

}