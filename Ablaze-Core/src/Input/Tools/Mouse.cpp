#include "Mouse.h"
#include "Graphics/Window.h"
#include "Graphics/Context.h"

namespace Ablaze
{

	maths::vec3 Mouse::position = maths::vec3(0, 0, 0);
	maths::vec3 Mouse::movedThisFrame = maths::vec3(0, 0, 0);
	maths::vec2 Mouse::relativeScroll = maths::vec2(0, 0);
	bool Mouse::onWindow = true;
	bool Mouse::buttons[MAX_BUTTONS];

	maths::vec3 Mouse::GetPosition(const Position& mode)
	{
		if (mode == Position::TopLeft)
		{
			return position;
		}
		else
		{
			return maths::vec3(position.x, Context::Window()->GetHeight() - position.y, 0);
		}
	}

	maths::vec3 Mouse::GetRelPosition(const Position& mode)
	{
		if (mode == Position::TopLeft)
		{
			return movedThisFrame;
		}
		else
		{
			return maths::vec3(movedThisFrame.x, Context::Window()->GetHeight() - movedThisFrame.y, 0);
		}
	}

	const maths::vec2& Mouse::GetRelativeScroll()
	{
		return relativeScroll;
	}

	void Mouse::Capture()
	{
		glfwSetInputMode(Context::Window()->GetWindowPtr(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	}

	void Mouse::Release()
	{
		glfwSetInputMode(Context::Window()->GetWindowPtr(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}

	bool Mouse::TestButton(int button)
	{
		return buttons[button];
	}

	bool Mouse::OnWindow()
	{
		return onWindow;
	}

	void Mouse::Update()
	{
		movedThisFrame = maths::vec3(0, 0, 0);
	}

	void Mouse::_MousePosCallback(GLFWwindow* window, double x, double y)
	{
		movedThisFrame = maths::vec3((float)x, (float)y, 0) - position; 
		position = maths::vec3((float)x, (float)y, 0);
	}

	void Mouse::_MouseEnteredCallback(GLFWwindow* window, int entered)
	{
		onWindow = (bool)entered;
	}

	void Mouse::_MouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
	{
		if (action == GLFW_PRESS)
		{
			buttons[button] = true;
		}
		else if (action == GLFW_RELEASE)
		{
			buttons[button] = false;
		}
	}

	void Mouse::_MouseScrollCallback(GLFWwindow* window, double xScroll, double yScroll)
	{
		relativeScroll = maths::vec2((float)xScroll, (float)yScroll);
	}

}