#pragma once
#include "AblazeGL.h"
#include "Types.h"

namespace Ablaze
{

#define MAX_KEYS 1024

	class Window;

	class Keyboard
	{
	private:
		static Window& window;
		static bool keys[MAX_KEYS];

	public:
		static bool TestKey(int key);

		static void _KeyboardKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
		static void _KeyboardCharCallback(GLFWwindow* window, uint codepoint);

	};

}