#pragma once
#include "HeightFunction.h"
#include "Utils/Files/ImageFile.h"

namespace Ablaze
{

	class HeightmapFunction : public HeightFunction
	{
	private:
		ImageFile* heightmap;
		float maxHeight;
		int x;
		int y;

	public:
		HeightmapFunction(ImageFile* const heightmap, float maxHeight, int startX = 0, int startY = 0);

		void SetX(int x);
		void SetY(int y);
		std::vector<float> Generate(int xVerts, int yVerts) const override;

	};

}