#pragma once
#include "Window.h"

namespace Ablaze
{

	class Context
	{
	private:
		static Window* window;

	public:
		static bool Initialised();
		static void SetWindow(Window* window);
		static Window* Window();

	};

}