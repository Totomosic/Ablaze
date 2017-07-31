#include "MeshComponent.h"
#include "RenderEngine/structs/Mesh.h"
#include "Factories/MeshFactory.h"

namespace Ablaze
{
	namespace Components
	{

		MeshComponent::MeshComponent(Mesh* mesh)
			: mesh(mesh)
		{
			
		}

		MeshComponent::MeshComponent(const String& meshName) : MeshComponent(MeshFactory::Request(meshName))
		{
		
		}

		MeshComponent::~MeshComponent()
		{
			MeshFactory::Release(mesh);		
		}

		Mesh* MeshComponent::GetMesh() const
		{
			return mesh;
		}

		void MeshComponent::SetMesh(Mesh* mesh)
		{
			MeshFactory::Release(this->mesh);
			this->mesh = mesh;
		}

		void MeshComponent::SetMesh(const String& meshName)
		{
			SetMesh(MeshFactory::Request(meshName));
		}

		Component* MeshComponent::Clone()
		{
			MeshComponent* m = new MeshComponent(MeshFactory::Request(mesh));
			return m;
		}

	}
}