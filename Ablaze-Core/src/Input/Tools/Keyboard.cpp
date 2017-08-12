#include "Keyboard.h"
#include "Graphics/Context.h"

namespace Ablaze
{

	Window& Keyboard::window = *(Context::Window());
	bool Keyboard::keys[MAX_KEYS];
	std::vector<int> Keyboard::pressedThisFrame;

	bool Keyboard::TestKey(int key)
	{
		return keys[key];
	}

	bool Keyboard::KeyPressed(int key)
	{
		return std::find(pressedThisFrame.begin(), pressedThisFrame.end(), key) != pressedThisFrame.end();
	}

	void Keyboard::Update()
	{
		pressedThisFrame.clear();
	}

	void Keyboard::_KeyboardKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		if (action == GLFW_PRESS)
		{
			keys[key] = true;
			pressedThisFrame.push_back(key);
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