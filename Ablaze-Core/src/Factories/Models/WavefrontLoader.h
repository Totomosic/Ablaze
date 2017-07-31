#pragma once
#include "RenderEngine/structs/Model.h"
#include "Utils/Files/WavefrontFile.h"
#include "Utils/Funcs.h"
#include "Types.h"

namespace Ablaze
{
	namespace Internal
	{
		class WavefrontLoader
		{
		public:
			struct VertexSet
			{
				std::vector<maths::vec3> positions, normals;
				std::vector<maths::vec2> uvs;
			};

			struct IndexSet
			{
				uint position;
				uint uv;
				uint normal;

				bool operator==(const IndexSet& other) const
				{
					return position == other.position && uv == other.uv && normal == other.normal;
				}

				friend struct std::hash<IndexSet>;
			};

		public:
			WavefrontLoader() { }

			static Model* LoadModel(const String& name, const WavefrontFile* const file);
			static void InsertVertex(std::vector<Vertex>& vertices, std::vector<uint>& indices, std::unordered_map<IndexSet, int>& mapping, VertexSet& inputVertices, IndexSet& indexSet);

		private:


		};
	}
}