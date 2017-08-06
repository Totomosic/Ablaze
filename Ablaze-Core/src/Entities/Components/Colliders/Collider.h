#pragma once
#include "Entities/Components/Component.h"
#include "Scene/Scene.h"
#include "Types.h"

namespace Ablaze
{
	namespace Components
	{

		class Collider : public Component
		{
		protected:
			std::vector<std::pair<maths::vec3, BoundingBox>*> boundingBoxes;

		protected:
			Collider(const std::vector<std::pair<maths::vec3, BoundingBox>*>& boundingBoxes);

		public:
			Collider(const BoundingBox& boundingBox, const maths::vec3& positionOffset = maths::vec3(0.0f));
			Collider(Model* model, const maths::vec3& positionOffset = maths::vec3(0.0f));
			Collider(const String& modelName, const maths::vec3& positionOffset = maths::vec3(0.0f));
			Collider();

			int GetCount() const;
			const BoundingBox& GetBoundingBox(int index = 0) const;
			const maths::vec3& GetPositionOffset(int index = 0) const;

			void AddBoundingBox(const BoundingBox& boundingBox, const maths::vec3& positionOffset = maths::vec3(0.0f));

			Component* Clone() override;

			static Collider* FromMeshComponent(GameObject* object, bool useModelTransforms = true);
		};

	}
}