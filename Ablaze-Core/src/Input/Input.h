#pragma once
#include "Graphics/Context.h"
#include "Tools/Mouse.h"
#include "Tools/Keyboard.h"

namespace Ablaze
{

	class Input
	{
	private:

	public:
		static void PollEvents();

		static const bool MouseOnWindow();
		static const maths::vec3 NormalizedMousePosition();
		static const maths::vec3 MousePosition();
		static const maths::vec2 MouseScroll();
		static const bool MouseButtonDown(int button);
		static const bool MouseButtonUp(int button);

		static const bool KeyDown(int key);
		static const bool KeyUp(int key);


	};

}