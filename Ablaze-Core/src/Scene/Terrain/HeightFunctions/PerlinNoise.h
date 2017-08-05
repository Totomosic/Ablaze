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
		PerlinNoise(float min, float max, float smoothness);

		std::vector<float> Generate(const maths::vec2& terrainSize, int vertexResolution) const override;

	};

}