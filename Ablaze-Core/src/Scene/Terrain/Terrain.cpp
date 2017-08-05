#include "Terrain.h"
#include "TerrainData.h"

namespace Ablaze
{

	Terrain::Terrain(const String& name, const maths::vec2& size, int vertexResolution) : Model(name, new VBO(vertexResolution * vertexResolution * sizeof(Vertex), 0), new IndexBuffer((int)((vertexResolution - 1) * (vertexResolution - 1) * 6 *sizeof(GLuint))), maths::vec3(size.x, 0, size.y))
	{
		terrainData = new TerrainData(this, size, vertexResolution);
		CreateIndexBuffer();
	}

	Terrain::~Terrain()
	{
		delete terrainData;
	}

	float Terrain::GetWidth() const
	{
		return terrainData->GetSize().x;
	}

	float Terrain::GetHeight() const
	{
		return terrainData->GetSize().y;
	}

	int Terrain::GetResolution() const
	{
		return terrainData->GetVertexResolution();
	}

	TerrainData* Terrain::GetData()
	{
		return terrainData;
	}

	void Terrain::Recreate()
	{
		terrainData->Recreate();
	}

	void Terrain::SetData(TerrainData* data)
	{
		terrainData = data;
		data->SetTerrain(this);
	}

	void Terrain::Generate(const HeightFunction& function)
	{
		SetData(new TerrainData(this, terrainData->GetSize(), GetResolution(), function.Generate(terrainData->GetSize(), GetResolution())));
	}

	void Terrain::CreateIndexBuffer()
	{
		GLuint* indices = (GLuint*)indexBuffer->MapBuffer(Access::Write);
		for (int j = 0; j < GetResolution() - 1; j++)
		{
			for (int i = 0; i < GetResolution() - 1; i++)
			{
				*indices = i + j * GetResolution();
				indices++;
				*indices = i + (j + 1) * GetResolution();
				indices++;
				*indices = i + 1 + (j + 1) * GetResolution();
				indices++;
				*indices = i + j * GetResolution();
				indices++;
				*indices = i + 1 + (j + 1) * GetResolution();
				indices++;
				*indices = i + 1 + j * GetResolution();
				indices++;
			}
		}
		indexBuffer->UnmapBuffer();
	}

}