#include "TerrainData.h"
#include "Terrain.h"
#include "Scene/Terrain/HeightFunctions/HeightFunction.h"

namespace Ablaze
{

	TerrainData::TerrainData(Terrain* const terrain, const maths::vec2& size, int vertexResolution)
		: terrain(terrain), size(size), vertexResolution(vertexResolution)
	{
		Reset(0.0f);
	}

	TerrainData::TerrainData(Terrain* const terrain, const maths::vec2& size, int vertexResolution, const std::vector<float>& heights) : TerrainData(terrain, size, vertexResolution)
	{
		SetData(heights);
	}

	TerrainData::TerrainData(Terrain* const terrain, const maths::vec2& size, int vertexResolution, const HeightFunction& function) : TerrainData(terrain, size, vertexResolution, function.Generate(size, vertexResolution))
	{
	
	}

	const Terrain* TerrainData::GetTerrain() const
	{
		return terrain;
	}

	const maths::vec2& TerrainData::GetSize() const
	{
		return size;
	}

	int TerrainData::GetVertexResolution() const
	{
		return vertexResolution;
	}

	float TerrainData::GetVertexHeight(int x, int y) const
	{
		return heightData[To1DIndex(x, y)];
	}

	void TerrainData::SetTerrain(Terrain* const terrain)
	{
		this->terrain = terrain;
	}

	void TerrainData::Recreate()
	{
		SetData(heightData);
	}

	void TerrainData::Reset(float restHeight)
	{
		heightData.clear();
		for (int i = 0; i < vertexResolution * vertexResolution; i++)
		{
			heightData.push_back(restHeight);
		}
		ApplyToModel();
	}

	void TerrainData::SetData(const std::vector<float>& data)
	{
		heightData = data;
		ApplyToModel();
	}

	void TerrainData::SetData(const HeightFunction& function)
	{
		SetData(function.Generate(size, vertexResolution));
	}

	void TerrainData::SetVertexHeight(int x, int y, float height)
	{
		heightData[To1DIndex(x, y)] = height;
		SetModelVertex(x, y, height);
	}

	int TerrainData::To1DIndex(int x, int y) const
	{
		return x + y * vertexResolution;
	}

	void TerrainData::ApplyToModel()
	{
		Vertex* ptr = (Vertex*)terrain->vbo->MapBuffer(Access::Write);
		for (int i = 0; i < vertexResolution; i++)
		{
			for (int j = 0; j < vertexResolution; j++)
			{
				ptr->position = maths::vec3(-size.x / 2.0f + i / (float)(vertexResolution - 1) * size.x, heightData[To1DIndex(i, j)], -size.y / 2.0f + j / (float)(vertexResolution - 1) * size.y);
				ptr->normal = maths::vec3(0, 1, 0); // TODO: Change
				ptr->texCoord = maths::vec2(i / (float)vertexResolution, j / (float)vertexResolution); // TODO: investigate
				ptr->color = Color::White();
				ptr->tangent = maths::vec3(0, 0, 1);
				ptr++;
			}
		}
		terrain->vbo->UnmapBuffer();
	}

	void TerrainData::SetModelVertex(int x, int y, float value)
	{
		int index = To1DIndex(x, y);
		int offset = index * terrain->vbo->GetLayout().GetStride() + sizeof(float);
		terrain->vbo->Bind();
		glBufferSubData(terrain->vbo->GetTarget(), offset, sizeof(float), &value);
	}

}