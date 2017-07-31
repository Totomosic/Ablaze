#include "Keyboard.h"
#include "Graphics/Context.h"

namespace Ablaze
{

	Window& Keyboard::window = *(Context::Window());
	bool Keyboard::keys[MAX_KEYS];

	bool Keyboard::TestKey(int key)
	{
		return keys[key];
	}

	void Keyboard::_KeyboardKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		if (action == GLFW_PRESS)
		{
			keys[key] = true;
		}
		else if (action == GLFW_RELEASE)
		{
			keys[key] = false;
		}
	}

	void Keyboard::_KeyboardCharCallback(GLFWwindow* window, uint codepoint)
	{
		
	}

}