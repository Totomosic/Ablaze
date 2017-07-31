#pragma once
#include "Components\ComponentSet.h"
#include "Maths\Maths.h"

#define GAME_OBJECT_ANCHOR 0

namespace Ablaze
{

	class Layer;

	namespace Components
	{
		class Transform;
		class Parent;
		class Identifier;
		class Renderer;
		class MeshComponent;
	}

	class GameObject
	{
	private:
		static GameObject** gameObjects;
		static uint highestID;

	protected:
		static GameObject* anchorObject; // All GameObjects are children of anchor, most of the time will be positioned at (0, 0, 0)

		uint id;
		Layer* currentLayer;
		ComponentSet* components;

	protected:
		GameObject(bool anchor); // Anchor constructor
		virtual ~GameObject(); // Prevents stack objects

	public:
		GameObject(const maths::vec3& position, const maths::mat4& rotation = maths::mat4::Identity(), const maths::vec3& scale = maths::vec3(1, 1, 1));
		GameObject(float x, float y, float z, const maths::mat4& rotation = maths::mat4::Identity(), const maths::vec3& scale = maths::vec3(1, 1, 1));
		GameObject(const GameObject* parent, bool preserveCurrentPosition = true);
		GameObject(); 				

		void Destroy();
		GameObject* Clone() const;
		void MakeChildOf(const GameObject* parent, bool preserveCurrentPosition = true);
		void MakeStandalone(bool preserveCurrentPosition = true);
		void SetLayer(Layer* layer);
		Layer* GetLayer() const;

		uint GetID() const;
		ComponentSet& GetComponentSet() const;
		bool IsValid() const;

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
		Components::Parent* Parent() const;
		Components::Renderer* Renderer() const;
		Components::Identifier* Identifier() const;
		Components::MeshComponent* Mesh() const;

		static GameObject* Empty();

		static GameObject* Instantiate(const GameObject* prefab);
		static GameObject* Instantiate(const GameObject* prefab, const maths::vec3& worldPosition);
		static GameObject* Instantiate(const GameObject* prefab, const GameObject* parent);
		static GameObject* Instantiate(const GameObject* prefab, const GameObject* parent, const maths::vec3& worldPosition);
		
		static GameObject* Anchor();
		static GameObject* GetAtID(uint ID);
		static bool IsValid(uint id);
		static uint GetHightestID();
		static void Initialise();

	private:
		static uint GetNextID();

	};

}