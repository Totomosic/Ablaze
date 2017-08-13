#include "Collider.h"
#include "RenderEngine/structs/Mesh.h"
#include "Entities/Components/Rendering/MeshComponent.h"

namespace Ablaze
{
	namespace Components
	{

		Collider::Collider(const std::vector<std::pair<maths::vec3, AABB>*>& boundingBoxes)
			: boundingBoxes(boundingBoxes)
		{

		}

		Collider::Collider(const AABB& boundingBox, const maths::vec3& positionOffset)
		{
			AddAABB(boundingBox, positionOffset);
		}

		Collider::Collider(Model* model, const maths::vec3& positionOffset) : Collider(AABB::FromModel(model), positionOffset)
		{
		
		}

		Collider::Collider(const String& modelName, const maths::vec3& positionOffset) : Collider(AABB::FromModel(modelName), positionOffset)
		{
		
		}

		Collider::Collider()
		{
			
		}

		int Collider::GetCount() const
		{
			return boundingBoxes.size();
		}

		const AABB& Collider::GetAABB(int index) const
		{
			return boundingBoxes[index]->second;
		}

		const maths::vec3& Collider::GetPositionOffset(int index) const
		{
			return boundingBoxes[index]->first;
		}

		void Collider::AddAABB(const AABB& boundingBox, const maths::vec3& positionOffset)
		{
			boundingBoxes.push_back(new std::pair<maths::vec3, AABB>(positionOffset, boundingBox));
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
				collider->AddAABB(AABB::FromModel(mesh->GetModel(i)), (useModelTransforms) ? mesh->GetTransform(i).GetColumn(3).xyz() : maths::vec3(0.0f));
			}
			return collider;
		}

	}
}