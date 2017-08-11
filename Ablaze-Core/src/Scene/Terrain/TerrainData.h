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
		std::vector<float> heightData; // Represented as a 1D array, listed in columns

	public:
		TerrainData(Terrain* const terrain, const maths::vec2& size, int vertexResolution);
		TerrainData(Terrain* const terrain, const maths::vec2& size, int vertexResolution, const std::vector<float>& heights);
		TerrainData(Terrain* const terrain, const maths::vec2& size, int vertexResolution, const HeightFunction& function);

		const Terrain* GetTerrain() const;
		const maths::vec2& GetSize() const;
		int GetVertexResolution() const;
		float GetVertexHeight(int x, int y) const;
		float GetHeightAtLocation(float x, float z) const;

		void Recreate();
		void SetTerrain(Terrain* const terrain);
		void Reset(float restHeight = 0.0f);
		void SetData(const std::vector<float>& data);
		void SetData(const HeightFunction& function);
		void SetRegionHeight(int x, int y, int width, int depth, std::vector<float> heights);
		void SetRegionHeight(int x, int y, int width, int depth, const HeightFunction& function);
		void SetRegionHeight(int x, int y, int width, int depth, float height);
		void SetVertexHeight(int x, int y, float height);

		void EnableEditing();
		void DisableEditing();

	private:
		void ApplyToModel();
		void SetModelVertex(int x, int y, float value);
		int To1DIndex(int x, int y) const;
		maths::vec3 CalculateNormal(int x, int y);

	};

}