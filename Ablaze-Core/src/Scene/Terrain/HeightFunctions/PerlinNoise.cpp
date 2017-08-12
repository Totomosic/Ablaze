#include "PerlinNoise.h"
#include "Log.h"

namespace Ablaze
{

	PerlinNoise::PerlinNoise(int seed, float amplitude, float smoothness, int iterations)
		: seed(seed), amplitude(amplitude), smoothness(smoothness), iterations(iterations)
	{
		AB_FATAL("Seed: " + std::to_string(seed));
	}

	float PerlinNoise::GetNoise(int x, int y) const
	{
		Random::SetSeed((x * 92421407) % 38564123 + y * 24674217 + seed);
		return Random::NextFloat(-1.0f, 1.0f);
	}

	float PerlinNoise::GetSmoothNoise(int x, int y) const
	{
		float corners = (GetNoise(x - 1, y - 1) + GetNoise(x + 1, y - 1) + GetNoise(x - 1, y + 1) + GetNoise(x + 1, y + 1)) / 8.0f;
		float sides = (GetNoise(x - 1, y) + GetNoise(x + 1, y) + GetNoise(x, y - 1) + GetNoise(x, y + 1)) / 4.0f;
		float center = (GetNoise(x, y)) / 2.0f;
		return corners + sides + center;
	}

	float PerlinNoise::Interpolate(float x, float y, float blend) const
	{
		double theta = blend * maths::PI;
		float f = (1.0f - cos(theta)) * 0.5f;
		return x * (1.0f - f) + y * f;
	}

	float PerlinNoise::GetInterpolatedNoise(float x, float y) const
	{
		int intX = (int)x;
		int intY = (int)y;
		float fracX = x - intX;
		float fracY = y - intY;

		float v1 = GetSmoothNoise(intX, intY);
		float v2 = GetSmoothNoise(intX + 1, intY);
		float v3 = GetSmoothNoise(intX, intY + 1);
		float v4 = GetSmoothNoise(intX + 1, intY + 1);
		float i1 = Interpolate(v1, v2, fracX);
		float i2 = Interpolate(v3, v4, fracX);
		return Interpolate(i1, i2, fracY);
	}

	std::vector<float> PerlinNoise::Generate(int xVerts, int yVerts) const
	{
		std::vector<float> heights;
		for (int i = 0; i < xVerts; i++)
		{
			for (int j = 0; j < yVerts; j++)
			{
				float height = 0;
				for (int k = 0; k < iterations; k++)
				{
					height += GetInterpolatedNoise(i / smoothness / (float)pow(2, k), j / smoothness / (float)pow(2, k)) * amplitude / ((float)pow(2, k) / 2.0f);
				}
				heights.push_back(height);
			}
		}
		return heights;
	}

}