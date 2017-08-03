#include "WavefrontLoader.h"

template<>
struct std::hash<Ablaze::Internal::WavefrontLoader::IndexSet>
{
	const size_t operator()(const Ablaze::Internal::WavefrontLoader::IndexSet& key) const
	{
		return (key.position) ^ (key.normal << 14) ^ (key.uv << 23);
	}
};

namespace Ablaze
{
	namespace Internal
	{

		void UpdateMinMax(float x, float y, float z, float* minX, float* maxX, float* minY, float* maxY, float* minZ, float* maxZ)
		{
			if (x < *minX)
			{
				*minX = x;
			}
			if (x > *maxX)
			{
				*maxX = x;
			}
			if (y < *minY)
			{
				*minY = y;
			}
			if (y > *maxY)
			{
				*maxY = y;
			}
			if (z < *minZ)
			{
				*minZ = z;
			}
			if (z > *maxZ)
			{
				*maxZ = z;
			}
		}

		Model* WavefrontLoader::LoadModel(const String& name, WavefrontFile* const file)
		{
			file->Open(OpenMode::Read);
			std::vector<String> lines = Utils::SplitString(file->Read(), "\n");
			file->Close();
			VertexSet inputVertices;
			std::vector<Vertex> vertices;
			std::vector<uint> indices;
			std::unordered_map<IndexSet, int> mapping;

			float minX = (float)+1e10;
			float maxX = (float)-1e10;
			float minY = (float)+1e10;
			float maxY = (float)-1e10;
			float minZ = (float)+1e10;
			float maxZ = (float)-1e10;

			uint i = 0;
			for (String line : lines)
			{
				const char* cstr = line.c_str();
				if (strstr(cstr, "#")) // Comment
				{
					continue;
				}
				if (strstr(cstr, "mtl")) // material
				{
					continue;
				}
				if (strstr(cstr, "s")) // ??
				{
					continue;
				}
				if (strstr(cstr, "g")) // ??
				{
					continue;
				}
				if (strstr(cstr, "off")) // ??
				{
					continue;
				}
				else if (strstr(cstr, "v"))
				{
					if (strstr(cstr, "vt"))
					{
						maths::vec2 uv;
						int result = sscanf(cstr, "%*s %f %f", &uv.x, &uv.y);
						if (result == 0)
							continue;
						inputVertices.uvs.push_back(uv);
					}
					else if (strstr(cstr, "vn"))
					{
						maths::vec3 normal;
						int result = sscanf(cstr, "%*s %f %f %f", &normal.x, &normal.y, &normal.z);
						if (result == 0)
							continue;
						inputVertices.normals.push_back(normal);
					}
					else
					{
						maths::vec3 position;
						int result = sscanf(cstr, "%*s %f %f %f", &position.x, &position.y, &position.z);
						UpdateMinMax(position.x, position.y, position.z, &minX, &maxX, &minY, &maxY, &minZ, &maxZ);
						if (result == 0)
							continue;
						inputVertices.positions.push_back(position);
					}
				}
				else if (strstr(cstr, "f"))
				{
					IndexSet firstIndexSet[4];
					IndexSet indexSet[3];
					int result = sscanf(cstr, "%*s %d/%d/%d %d/%d/%d %d/%d/%d %d/%d/%d", &firstIndexSet[0].position, &firstIndexSet[0].uv, &firstIndexSet[0].normal, &firstIndexSet[1].position, &firstIndexSet[1].uv, &firstIndexSet[1].normal, &firstIndexSet[2].position, &firstIndexSet[2].uv, &firstIndexSet[2].normal, &firstIndexSet[3].position, &firstIndexSet[3].uv, &firstIndexSet[3].normal);
					if (result == 12)
					{
						InsertVertex(vertices, indices, mapping, inputVertices, firstIndexSet[0]);
						InsertVertex(vertices, indices, mapping, inputVertices, firstIndexSet[1]);
						InsertVertex(vertices, indices, mapping, inputVertices, firstIndexSet[2]);
						InsertVertex(vertices, indices, mapping, inputVertices, firstIndexSet[0]);
						InsertVertex(vertices, indices, mapping, inputVertices, firstIndexSet[2]);
						InsertVertex(vertices, indices, mapping, inputVertices, firstIndexSet[3]);
					}
					else
					{						
						result = sscanf(cstr, "%*s %d/%d/%d %d/%d/%d %d/%d/%d", &indexSet[0].position, &indexSet[0].uv, &indexSet[0].normal, &indexSet[1].position, &indexSet[1].uv, &indexSet[1].normal, &indexSet[2].position, &indexSet[2].uv, &indexSet[2].normal);
						if (result == 9)
						{
							InsertVertex(vertices, indices, mapping, inputVertices, indexSet[0]);
							InsertVertex(vertices, indices, mapping, inputVertices, indexSet[1]);
							InsertVertex(vertices, indices, mapping, inputVertices, indexSet[2]);
						}
						else
						{
							result = sscanf(cstr, "%*s %d//%d %d//%d %d//%d %d//%d", &firstIndexSet[0].position, &firstIndexSet[0].normal, &firstIndexSet[1].position, &firstIndexSet[1].normal, &firstIndexSet[2].position, &firstIndexSet[2].normal, &firstIndexSet[3].position, &firstIndexSet[3].normal);
							if (result == 8)
							{
								firstIndexSet[0].uv = 0;
								firstIndexSet[1].uv = 0;
								firstIndexSet[2].uv = 0;
								firstIndexSet[3].uv = 0;
								InsertVertex(vertices, indices, mapping, inputVertices, firstIndexSet[0]);
								InsertVertex(vertices, indices, mapping, inputVertices, firstIndexSet[1]);
								InsertVertex(vertices, indices, mapping, inputVertices, firstIndexSet[2]);
								InsertVertex(vertices, indices, mapping, inputVertices, firstIndexSet[0]);
								InsertVertex(vertices, indices, mapping, inputVertices, firstIndexSet[2]);
								InsertVertex(vertices, indices, mapping, inputVertices, firstIndexSet[3]);
							}
							else
							{
								result = sscanf(cstr, "%*s %d//%d %d//%d %d//%d", &indexSet[0].position, &indexSet[0].normal, &indexSet[1].position, &indexSet[1].normal, &indexSet[2].position, &indexSet[2].normal);
								if (result == 6)
								{
									indexSet[0].uv = 0;
									indexSet[1].uv = 0;
									indexSet[2].uv = 0;
									InsertVertex(vertices, indices, mapping, inputVertices, indexSet[0]);
									InsertVertex(vertices, indices, mapping, inputVertices, indexSet[1]);
									InsertVertex(vertices, indices, mapping, inputVertices, indexSet[2]);
								}
								else
								{
									AB_ERROR("Skipped face");
									continue;
								}
							}
						}
					}
				}
				/*if (i++ % 1000 == 0)
				{
					AB_INFO(std::to_string((int)((i / (float)lines.size()) * 100.0f)) + "%");
				)*/
			}
			VBO* vbo = new VBO(vertices.size() * sizeof(Vertex), 0);
			vbo->Bind();
			vbo->Upload(&vertices[0], vertices.size() * sizeof(Vertex));

			IndexBuffer* ib = new IndexBuffer(indices.size() * sizeof(GLuint), &indices[0]);
			Model* model = new Model(name, vbo, ib, maths::vec3(maxX - minX, maxY - minY, maxZ - minZ));
			model->GetVAO()->SetPrimitiveType(GL_TRIANGLES);
			return model;
		}

		void WavefrontLoader::InsertVertex(std::vector<Vertex>& vertices, std::vector<uint>& indices, std::unordered_map<IndexSet, int>& mapping, VertexSet& inputVertices, IndexSet& indexSet)
		{
			auto lookup = mapping.find(indexSet);
			if (lookup != mapping.end())
			{
				indices.push_back(lookup->second);
			}
			else
			{
				mapping[indexSet] = (int)vertices.size();
				indices.push_back(vertices.size());
				if (indexSet.uv == 0)
				{
					Vertex vertex = { inputVertices.positions[indexSet.position - 1], inputVertices.normals[indexSet.normal - 1], maths::vec2(0, 0), Color::White(), maths::vec3(0, 0, 1) };
					vertices.push_back(vertex);
				}
				else
				{
					Vertex vertex = { inputVertices.positions[indexSet.position - 1], inputVertices.normals[indexSet.normal - 1], inputVertices.uvs[indexSet.uv - 1], Color::White(), maths::vec3(0, 0, 1) };
					vertices.push_back(vertex);
				}
			}
		}
	}
}