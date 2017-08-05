#include "PerlinNoise.h"

namespace Ablaze
{

	PerlinNoise::PerlinNoise(float minVal, float maxVal , float smoothness)
		: minHeight(minVal), maxHeight(maxVal), smoothness(smoothness)
	{
		
	}

	std::vector<float> PerlinNoise::Generate(int xVerts, int yVerts) const
	{
		std::vector<float> heights;
		for (int i = 0; i < xVerts; i++)
		{
			for (int j = 0; j < yVerts; j++)
			{
				heights.push_back(Random::NextFloat(minHeight, maxHeight));
			}
		}
		return heights;
	}

}