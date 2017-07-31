#include "GameObject.h"
#include "Engine.h"
#include "Tags.h"
#include "Components\Components.h"
#include "Scene\Layer.h"
#include "Factories\MeshFactory.h"

namespace Ablaze
{

	GameObject** GameObject::gameObjects = new GameObject*[AblazeEngine::maxEntities];
	uint GameObject::highestID = 0;

	GameObject* GameObject::anchorObject = nullptr;

	GameObject::GameObject(bool anchor)
	{
		id = GAME_OBJECT_ANCHOR;
		gameObjects[id] = this;
		components = new ComponentSet(*this);

		if (Layer::GetCurrentLayer() != nullptr)
		{
			SetLayer(Layer::GetCurrentLayer());
		}

		AddComponent(new Components::Transform());
		AddComponent(new Components::Identifier(Tags::Anchor));
	}

	GameObject::GameObject(const maths::vec3& position, const maths::mat4& rotation, const maths::vec3& scale)
	{
		id = GetNextID();
		gameObjects[id] = this;
		currentLayer = nullptr;
		components = new ComponentSet(*this);

		if (Layer::GetCurrentLayer() != nullptr)
		{
			SetLayer(Layer::GetCurrentLayer());
		}

		// Add Default Components
		AddComponent(new Components::Transform(position, rotation, scale));
		AddComponent(new Components::Parent(Anchor())); // All objects are a child of the Anchor Object
		AddComponent(new Components::Identifier(Tags::None));
		AddComponent(new Components::MeshComponent(MeshFactory::BuildCuboidUnnamed(maths::vec3(1, 1, 1), Color::White(), MaterialFactory::Build("Default", Color::White(), Shader::Default()))));
		// TODO: add Renderer Component
	}

	GameObject::GameObject(float x, float y, float z, const maths::mat4& rotation, const maths::vec3& scale) : GameObject(maths::vec3(x, y, z), rotation, scale)
	{
	
	}

	GameObject::GameObject() : GameObject::GameObject(maths::vec3(0, 0, 0))
	{
		
	}

	GameObject::GameObject(const GameObject* parent, bool preserveCurrentPosition) : GameObject()
	{
		MakeChildOf(parent, preserveCurrentPosition);
		SetLayer(parent->GetLayer());
	}

	GameObject::~GameObject()
	{
		delete components;
		gameObjects[id] = nullptr;
	}

	void GameObject::Destroy()
	{
		SetLayer(nullptr);
		gameObjects[id] = nullptr;
		delete this;
	}

	GameObject* GameObject::Clone() const
	{
		return Instantiate(this);
	}

	void GameObject::MakeChildOf(const GameObject* parent, bool preserveCurrentPosition)
	{
		if (preserveCurrentPosition && GetComponentSet().HasComponent<Components::Parent>() && parent->GetComponentSet().HasComponent<Components::Transform>())
		{
			Components::Transform* thisTransform = Transform();
			Components::Transform* parentTransform = parent->Transform();
			thisTransform->SetPosition(thisTransform->GetPosition() - parentTransform->GetPosition());
		}
		AddComponent(new Components::Parent(parent));
	}

	void GameObject::MakeStandalone(bool preserveCurrentPosition)
	{
		
		if (components->HasComponent<Components::Parent>() && preserveCurrentPosition)
		{
			Components::Parent* parent = GetComponent<Components::Parent>();
			if (components->HasComponent<Components::Transform>() && parent->GetParentObject()->components->HasComponent<Components::Transform>())
			{
				Components::Transform* thisTransform = Transform();
				Components::Transform* parentTransform = parent->GetParentObject()->Transform();
				thisTransform->SetPosition(thisTransform->GetPosition() + parentTransform->GetPosition());
			}
		}		
		GetComponentSet().RemoveComponent<Components::Parent>();
	}

	void GameObject::SetLayer(Layer* layer)
	{
		if (currentLayer != nullptr)
		{
			currentLayer->RemoveGameObject(this);
		}
		currentLayer = layer;		
		if (currentLayer != nullptr)
		{
			currentLayer->AddGameObject(this);
		}
	}

	Layer* GameObject::GetLayer() const
	{
		return currentLayer;
	}

	uint GameObject::GetID() const
	{
		return id;
	}

	ComponentSet& GameObject::GetComponentSet() const
	{
		return *components;
	}


	Components::Transform* GameObject::Transform() const
	{
		return GetComponent<Components::Transform>();
	}

	Components::Parent* GameObject::Parent() const
	{
		return GetComponent<Components::Parent>();
	}

	Components::Renderer* GameObject::Renderer() const
	{
		return GetComponent<Components::Renderer>();
	}

	Components::Identifier* GameObject::Identifier() const
	{
		return GetComponent<Components::Identifier>();
	}

	Components::MeshComponent* GameObject::Mesh() const
	{
		return GetComponent<Components::MeshComponent>();
	}


	bool GameObject::IsValid() const
	{
		return gameObjects[id] != nullptr;
	}

	GameObject* GameObject::Anchor()
	{
		return gameObjects[GAME_OBJECT_ANCHOR];
	}

	GameObject* GameObject::GetAtID(uint ID)
	{
		return gameObjects[ID];
	}

	GameObject* GameObject::Empty()
	{
		GameObject* obj = new GameObject();
		obj->GetComponentSet().RemoveAll();
		return obj;
	}

	GameObject* GameObject::Instantiate(const GameObject* prefab)
	{
		GameObject* obj = Empty();
		for (auto comp : prefab->GetComponentSet().GetAll())
		{
			obj->AddComponent(comp->Clone());
		}
		obj->SetLayer(prefab->GetLayer());
		return obj;
	}

	GameObject* GameObject::Instantiate(const GameObject* prefab, const maths::vec3& position)
	{
		GameObject* obj = Instantiate(prefab);
		obj->AddComponent(new Components::Transform(position));
		return obj;
	}

	GameObject* GameObject::Instantiate(const GameObject* prefab, const GameObject* parent)
	{
		GameObject* obj = Instantiate(prefab);
		obj->AddComponent(new Components::Parent(parent));
		obj->SetLayer(parent->GetLayer());
		return obj;
	}

	GameObject* GameObject::Instantiate(const GameObject* prefab, const GameObject* parent, const maths::vec3& position)
	{
		GameObject* obj = Instantiate(prefab, position);
		obj->AddComponent(new Components::Parent(parent));
		obj->SetLayer(parent->GetLayer());
		return obj;
	}

	void GameObject::Initialise()
	{		
		for (int i = 0; i < AblazeEngine::maxEntities; i++)
		{
			gameObjects[i] = nullptr;
		}
		anchorObject = new GameObject(true);
	}

	uint GameObject::GetHightestID()
	{
		return highestID;
	}

	bool GameObject::IsValid(uint id)
	{
		return gameObjects[id] != nullptr;
	}

	uint GameObject::GetNextID()
	{
		for (int i = 0; i < highestID + 5; i++)
		{
			if (gameObjects[i] == nullptr)
			{
				if (i > highestID)
				{
					highestID = i;
				}
				return i;
			}
		}
		AB_ERROR("Could not find available ID for GameObject");
		return 0;
	}

}