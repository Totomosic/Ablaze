#pragma once
#include "Maths/Maths.h"
#include "Enums.h"

namespace Ablaze
{

#define MAX_BUTTONS 32

	class Window;

	class Mouse
	{
	private:
		static maths::vec3 position;
		static maths::vec3 movedThisFrame;
		static maths::vec2 relativeScroll;
		static bool buttons[MAX_BUTTONS];
		static bool onWindow; // entered or not
		// TODO: add image -> display fake cursor

	public:
		static const maths::vec3& GetPosition(const Position& mode = Position::TopLeft);
		static const maths::vec3& GetRelPosition(const Position& mode = Position::TopLeft);
		static const maths::vec2& GetRelativeScroll();

		static void Capture();
		static void Release();
		static bool TestButton(int button);
		static bool OnWindow();

		static void Update();

		static void _MousePosCallback(GLFWwindow* window, double x, double y);
		static void _MouseEnteredCallback(GLFWwindow* window, int entered);
		static void _MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
		static void _MouseScrollCallback(GLFWwindow* window, double xScroll, double yScroll);
	};
}