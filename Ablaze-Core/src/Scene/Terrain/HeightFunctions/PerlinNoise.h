#pragma once
#include "HeightFunction.h"
#include "Maths/Maths.h"

namespace Ablaze
{

	class PerlinNoise : public HeightFunction
	{
	private:
		float maxHeight;
		float minHeight;
		float smoothness;

	public:
		PerlinNoise(float minVal, float maxVal, float smoothness);

		std::vector<float> Generate(int xVerts, int yVerts) const override;

	};

}