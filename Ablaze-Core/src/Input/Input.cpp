#include "Input.h"

namespace Ablaze
{
	void Input::PollEvents()
	{
		glfwPollEvents();
	}

	const bool Input::MouseOnWindow()
	{
		return Mouse::OnWindow();
	}

	const maths::vec3 Input::NormalizedMousePosition()
	{
		return MousePosition() / maths::vec3(Context::Window()->GetWidth(), -Context::Window()->GetHeight(), 1) * 2 - maths::vec3(1, -1, 0);
	}

	const maths::vec3 Input::MousePosition()
	{
		return Mouse::GetPosition();
	}

	const maths::vec2 Input::MouseScroll()
	{
		return Mouse::GetRelativeScroll();
	}

	const bool Input::MouseButtonDown(int button)
	{
		return Mouse::TestButton(button);
	}

	const bool Input::MouseButtonUp(int button)
	{
		return !Mouse::TestButton(button);
	}

	const bool Input::KeyDown(int key)
	{
		return Keyboard::TestKey(key);
	}

	const bool Input::KeyUp(int key)
	{
		return !Keyboard::TestKey(key);
	}

}