#include "HeightmapFunction.h"
#include "Graphics/Resources/Imaging/ImageLoader.h"
#include "Graphics/Resources/Imaging/Textures/Texture2D.h"
#include "AblazeGL.h"

namespace Ablaze
{

	HeightmapFunction::HeightmapFunction(ImageFile* const heightmap, float maxHeight, int startX, int startY) : HeightFunction(),
		heightmap(heightmap), maxHeight(maxHeight), x(startX), y(startY)
	{

	}

	void HeightmapFunction::SetX(int x)
	{
		this->x = x;
	}

	void HeightmapFunction::SetY(int y)
	{
		this->y = y;
	}

	std::vector<float> HeightmapFunction::Generate(int xVerts, int yVerts) const
	{
		int width;
		int height;
		uint bpp;
		byte* pixels = heightmap->ReadImage(&width, &height, &bpp);
		std::vector<float> heights;

		for (int i = 0; i < xVerts * yVerts; i++)
		{
			byte pixelValue = pixels[i * (bpp / 8)];
			float height = (pixelValue - 128) / 255.0f * 2 * maxHeight;
			heights.push_back(height);
		}
		delete pixels;
		return heights;
	}

}