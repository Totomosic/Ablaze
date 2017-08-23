#pragma once
#include "Graphics/Resources/Mesh.h"
#include "Components/ComponentSet.h"

namespace Ablaze
{

	class Layer;

	class GameObject
	{
	protected:
		uint id;
		Layer* currentLayer;
		ComponentSet* components;

	protected:
		GameObject(bool anchor); // Anchor constructor
		virtual ~GameObject(); // Prevents stack objects

	public:
		GameObject(const maths::vec3& position, const maths::mat4& rotation = maths::mat4::Identity(), const maths::vec3& scale = maths::vec3(1, 1, 1));
		GameObject(float x, float y, float z, const maths::mat4& rotation = maths::mat4::Identity(), const maths::vec3& scale = maths::vec3(1, 1, 1));
		GameObject(const GameObject* parent, bool preserveCurrentPosition = false);
		GameObject(); 				

		virtual void Destroy();
		virtual GameObject* Clone() const;
		virtual void MakeChildOf(const GameObject* parent, bool preserveCurrentPosition = false);
		virtual void MakeStandalone(bool preserveCurrentPosition = true);
		virtual Layer* GetLayer() const;
		virtual void SetLayer(Layer* layer);

		uint GetID() const;
		ComponentSet& GetComponentSet() const;

		template<class T> T* GetComponent() const
		{
			return components->GetComponent<T>();
		}

		template<class T> bool HasComponent() const
		{
			return components->HasComponent<T>();
		}

		void AddComponent(Components::Component* component)
		{
			components->AddComponent(*component);
		}

		// Get Default Components
		Components::Transform* Transform() const;
		Components::Parent* ParentComponent() const;
		Components::Identifier* Identifier() const;
		Components::MeshComponent* Mesh() const;

		const GameObject* const Parent() const;
		void SetMesh(const String& meshName);
		void SetMesh(Ablaze::Mesh* mesh);

		static GameObject* Empty();

		static GameObject* Instantiate(const GameObject* prefab);
		static GameObject* Instantiate(const GameObject* prefab, const maths::vec3& worldPosition);
		static GameObject* Instantiate(const GameObject* prefab, const GameObject* parent);
		static GameObject* Instantiate(const GameObject* prefab, const GameObject* parent, const maths::vec3& worldPosition);

		friend class Scene;
		friend class ComponentSet;

	};

}