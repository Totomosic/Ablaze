#pragma once
#include "Types.h"
#include "Maths/Maths.h"
#include "AblazeGL.h"

namespace Ablaze
{

	class Terrain;
	class HeightFunction;

	class TerrainData
	{
	private:
		Terrain* terrain;
		maths::vec2 size;
		int vertexResolution;
		// 0, 1, 2, 3
		// 4, 5, 6, 7
		// 8, 9, 10, 11
		// 12, 13, 14, 15
		std::vector<float> heightData; // Represented as a 1D array, listed in rows 

	public:
		TerrainData(Terrain* const terrain, const maths::vec2& size, int vertexResolution);
		TerrainData(Terrain* const terrain, const maths::vec2& size, int vertexResolution, const std::vector<float>& heights);
		TerrainData(Terrain* const terrain, const maths::vec2& size, int vertexResolution, const HeightFunction& function);

		const Terrain* GetTerrain() const;
		const maths::vec2& GetSize() const;
		int GetVertexResolution() const;
		float GetVertexHeight(int x, int y) const;

		void Recreate();
		void SetTerrain(Terrain* const terrain);
		void Reset(float restHeight = 0.0f);
		void SetData(const std::vector<float>& data);
		void SetData(const HeightFunction& function);
		void SetVertexHeight(int x, int y, float height);

	private:
		void ApplyToModel();
		void SetModelVertex(int x, int y, float value);
		int To1DIndex(int x, int y) const;

	};

}