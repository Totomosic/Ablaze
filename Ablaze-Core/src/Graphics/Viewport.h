#pragma once
#include "AblazeGL.h"

namespace Ablaze
{

	class Viewport
	{
	private:
		int x;
		int y;
		int width;
		int height;

	public:
		Viewport(int xOffset, int yOffset, int width, int height);
		Viewport();

		int GetX() const;
		int GetY() const;
		int GetWidth() const;
		int GetHeight() const;
		float GetAspect() const;

		void SetX(int x);
		void SetY(int y);
		void SetWidth(int w);
		void SetHeight(int h);

		void Bind() const;
		void Unbind() const;

	};

}