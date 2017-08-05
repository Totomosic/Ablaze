#pragma once
#include "Types.h"
#include "RenderEngine/structs/Model.h"
#include "HeightFunctions/HeightFunction.h"

namespace Ablaze
{

	class Terrain : public Model
	{
	private:
		TerrainData* terrainData;

	public:
		Terrain(const String& name, const maths::vec2& size, int vertexResolution);
		~Terrain();

		float GetWidth() const;
		float GetHeight() const;
		int GetResolution() const;
		TerrainData* GetData();

		void Recreate();
		void SetData(TerrainData* data);
		void Generate(const HeightFunction& function);

		friend class TerrainData;

	private:
		void CreateIndexBuffer();

	};

}