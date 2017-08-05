#pragma once
#include "Scene/Terrain/TerrainData.h"

namespace Ablaze
{

	class HeightFunction
	{
	protected:
		HeightFunction();

	public:
		virtual std::vector<float> Generate(const maths::vec2& terrainSize, int vertexResolution) const = 0;

	};

}