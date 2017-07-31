#pragma once
#include "../Component.h"

namespace Ablaze
{

	class Mesh;

	namespace Components
	{
		class MeshComponent : public Component
		{
		private:
			Mesh* mesh;

		public:
			MeshComponent(Mesh* mesh);
			MeshComponent(const String& meshName);
			~MeshComponent();

			Mesh* GetMesh() const;
			void SetMesh(Mesh* mesh);
			void SetMesh(const String& meshName);

			Component* Clone() override;

		};
	}
}