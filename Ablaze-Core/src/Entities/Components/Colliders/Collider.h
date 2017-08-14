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
			std::vector<std::pair<maths::mat4, OBB>*> boundingBoxes;

		protected:
			Collider(const std::vector<std::pair<maths::mat4, OBB>*>& boundingBoxes);

		public:
			Collider(const OBB& boundingBox, const maths::mat4& transform = maths::mat4::Identity());
			//Collider(Model* model, const maths::vec3& positionOffset = maths::vec3(0.0f));
			//Collider(const String& modelName, const maths::vec3& positionOffset = maths::vec3(0.0f));
			Collider();

			int GetCount() const;
			const OBB& GetOBB(int index = 0) const;
			const maths::mat4& GetTransform(int index = 0) const;

			void AddOBB(const OBB& boundingBox, const maths::mat4& transform = maths::mat4::Identity());

			Component* Clone() override;

			static Collider* FromMeshComponent(GameObject* object, bool useModelTransforms = true);
		};

	}
}