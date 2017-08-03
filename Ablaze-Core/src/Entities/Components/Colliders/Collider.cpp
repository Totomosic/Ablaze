#include "Collider.h"
#include "RenderEngine/structs/Mesh.h"
#include "Entities/Components/Rendering/MeshComponent.h"

namespace Ablaze
{
	namespace Components
	{

		Collider::Collider(const std::vector<std::pair<maths::vec3, BoundingBox>*>& boundingBoxes)
			: boundingBoxes(boundingBoxes)
		{

		}

		Collider::Collider(const BoundingBox& boundingBox, const maths::vec3& positionOffset)
		{
			AddBoundingBox(boundingBox, positionOffset);
		}

		Collider::Collider(Model* model, const maths::vec3& positionOffset) : Collider(BoundingBox::FromModel(model), positionOffset)
		{
		
		}

		Collider::Collider(const String& modelName, const maths::vec3& positionOffset) : Collider(BoundingBox::FromModel(modelName), positionOffset)
		{
		
		}

		Collider::Collider()
		{
			
		}

		int Collider::GetCount() const
		{
			return boundingBoxes.size();
		}

		const BoundingBox& Collider::GetBoundingBox(int index) const
		{
			return boundingBoxes[index]->second;
		}

		const maths::vec3& Collider::GetPositionOffset(int index) const
		{
			return boundingBoxes[index]->first;
		}

		void Collider::AddBoundingBox(const BoundingBox& boundingBox, const maths::vec3& positionOffset)
		{
			boundingBoxes.push_back(new std::pair<maths::vec3, BoundingBox>(positionOffset, boundingBox));
		}

		Component* Collider::Clone()
		{
			Collider* c = new Collider(boundingBoxes);
			return c;
		}

		Collider* Collider::FromMeshComponent(GameObject* object, bool useModelTransforms)
		{
			Collider* collider = new Collider();
			Mesh* mesh = object->Mesh()->GetMesh();
			for (int i = 0; i < mesh->GetLength(); i++)
			{
				collider->AddBoundingBox(BoundingBox::FromModel(mesh->GetModel(i)), (useModelTransforms) ? mesh->GetTransform(i).GetColumn(3).xyz() : maths::vec3(0.0f));
			}
			return collider;
		}

	}
}