#pragma once
#include "HeightFunction.h"
#include "Maths/Maths.h"

namespace Ablaze
{

	class PerlinNoise : public HeightFunction
	{
	private:
		int seed;
		float amplitude;
		float smoothness;

	public:
		PerlinNoise(int seed, float amplitude, float smoothness);

		std::vector<float> Generate(int xVerts, int yVerts) const override;

		float GetNoise(int x, int y) const;
		float GetSmoothNoise(int x, int y) const;
		float Interpolate(float x, float y, float blend) const;
		float GetInterpolatedNoise(float x, float y) const;

	};

}