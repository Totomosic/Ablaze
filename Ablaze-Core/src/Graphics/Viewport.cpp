#include "Viewport.h"

namespace Ablaze
{
	
	Viewport::Viewport(int x, int y, int w, int h)
		: x(x), y(y), width(w), height(h)
	{
	
	}

	Viewport::Viewport() : Viewport(0, 0, 1280, 720)
	{
	
	}

	int Viewport::GetX() const
	{
		return x;
	}

	int Viewport::GetY() const
	{
		return y;
	}

	int Viewport::GetWidth() const
	{
		return width;
	}

	int Viewport::GetHeight() const
	{
		return height;
	}

	float Viewport::GetAspect() const
	{
		return (float)width / height;
	}

	void Viewport::SetX(int x)
	{
		this->x = x;
	}

	void Viewport::SetY(int y)
	{
		this->y = y;
	}

	void Viewport::SetWidth(int w)
	{
		width = w;
	}

	void Viewport::SetHeight(int h)
	{
		height = h;
	}

	void Viewport::Bind() const
	{
		glViewport(x, y, width, height);
	}

	void Viewport::Unbind() const
	{
	
	}

}