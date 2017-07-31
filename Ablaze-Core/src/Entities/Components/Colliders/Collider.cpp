#include "Collider.h"

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

	}
}