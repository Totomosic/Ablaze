#pragma once
#include "Scene/Terrain/TerrainData.h"

namespace Ablaze
{

	class HeightFunction
	{
	protected:
		HeightFunction();

	public:
		virtual std::vector<float> Generate(int xVerts, int yVerts) const = 0;

	};

}