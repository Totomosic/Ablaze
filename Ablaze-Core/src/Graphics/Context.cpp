#include "Context.h"

namespace Ablaze
{

	Window* Context::window = nullptr;

	Window* Context::Window()
	{
		return window;
	}

	void Context::SetWindow(Ablaze::Window* win)
	{
		window = win;
	}

	bool Context::Initialised()
	{
		return window != nullptr;
	}

}