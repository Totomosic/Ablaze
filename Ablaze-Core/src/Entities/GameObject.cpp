#include "GameObject.h"
#include "Engine.h"
#include "Tags.h"
#include "Scene/SceneManager.h"
#include "Factories/MeshFactory.h"

namespace Ablaze
{

	GameObject::GameObject(bool anchor)
	{
		id = 0;
		SceneManager::CurrentScene()->gameObjects[id] = this;
		components = new ComponentSet(*this);

		if (SceneManager::CurrentScene() != nullptr && SceneManager::CurrentScene()->CurrentLayer() != nullptr)
		{
			SceneManager::CurrentScene()->CurrentLayer()->AddGameObject(this);
		}

		AddComponent(new Components::Transform());
		AddComponent(new Components::Identifier(Tags::Anchor));
	}

	GameObject::GameObject(const maths::vec3& position, const maths::mat4& rotation, const maths::vec3& scale)
	{
		id = SceneManager::CurrentScene()->GetNextID();
		SceneManager::CurrentScene()->gameObjects[id] = this;
		currentLayer = SceneManager::CurrentScene()->CurrentLayer();
		components = new ComponentSet(*this);

		parent = nullptr;

		if (SceneManager::CurrentScene() != nullptr && SceneManager::CurrentScene()->CurrentLayer() != nullptr)
		{
			SceneManager::CurrentScene()->CurrentLayer()->AddGameObject(this);
			parent = SceneManager::CurrentScene()->Anchor();
		}

		// Add Default Components
		AddComponent(new Components::Transform(position, rotation, scale));
		AddComponent(new Components::Identifier(Tags::None));
		AddComponent(new Components::MeshComponent(MeshFactory::BuildCuboidUnnamed(maths::vec3(1, 1, 1), Color::White(), MaterialFactory::Fabricate(Color::White(), Shader::Default()))));
	}

	GameObject::GameObject(float x, float y, float z, const maths::mat4& rotation, const maths::vec3& scale) : GameObject(maths::vec3(x, y, z), rotation, scale)
	{
	
	}

	GameObject::GameObject() : GameObject::GameObject(maths::vec3(0, 0, 0))
	{
		
	}

	GameObject::GameObject(GameObject* parent, bool preserveCurrentPosition) : GameObject()
	{
		parent->GetLayer()->AddGameObject(this);
		MakeChildOf(parent, preserveCurrentPosition);
	}

	GameObject::~GameObject()
	{
		delete components;
		SceneManager::CurrentScene()->gameObjects[id] = nullptr;
	}

	void GameObject::Destroy()
	{
		if (currentLayer != nullptr)
		{
			currentLayer->RemoveGameObject(this);
		}
		delete this;
	}

	GameObject* GameObject::Clone() const
	{
		return Instantiate(this);
	}

	void GameObject::MakeChildOf(GameObject* parent, bool preserveCurrentPosition)
	{
		if (preserveCurrentPosition && this->parent != nullptr && parent->GetComponentSet().HasComponent<Components::Transform>())
		{
			Components::Transform* thisTransform = Transform();
			Components::Transform* parentTransform = parent->Transform();
			thisTransform->SetPosition(thisTransform->GetPosition() - parentTransform->GetPosition());
		}
		this->parent = parent;
	}

	void GameObject::MakeStandalone(bool preserveCurrentPosition)
	{		
		if (parent != nullptr && preserveCurrentPosition)
		{
			if (components->HasComponent<Components::Transform>() && parent->components->HasComponent<Components::Transform>())
			{
				Components::Transform* thisTransform = Transform();
				Components::Transform* parentTransform = parent->Transform();
				thisTransform->SetPosition(thisTransform->GetPosition() + parentTransform->GetPosition());
			}
		}		
		parent = nullptr;
	}

	Layer* GameObject::GetLayer() const
	{
		return currentLayer;
	}

	bool GameObject::HasParent() const
	{
		return parent != nullptr;
	}

	void GameObject::SetLayer(Layer* layer)
	{
		if (currentLayer != nullptr)
		{
			currentLayer->RemoveGameObject(this);
		}
		currentLayer = layer;
		if (layer != nullptr)
		{
			currentLayer->AddGameObject(this);
		}
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

	Components::Identifier* GameObject::Identifier() const
	{
		return GetComponent<Components::Identifier>();
	}

	Components::MeshComponent* GameObject::Mesh() const
	{
		return GetComponent<Components::MeshComponent>();
	}

	GameObject* const GameObject::Parent() const
	{
		return parent;
	}

	void GameObject::SetMesh(Ablaze::Mesh* mesh)
	{
		Mesh()->SetMesh(mesh);
	}

	void GameObject::SetMesh(const String& meshName)
	{
		Mesh()->SetMesh(meshName);
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

	GameObject* GameObject::Instantiate(const GameObject* prefab, GameObject* parent)
	{
		GameObject* obj = Instantiate(prefab);
		obj->parent = parent;
		obj->SetLayer(parent->GetLayer());
		return obj;
	}

	GameObject* GameObject::Instantiate(const GameObject* prefab, GameObject* parent, const maths::vec3& position)
	{
		GameObject* obj = Instantiate(prefab, position);
		obj->parent = parent;
		obj->SetLayer(parent->GetLayer());
		return obj;
	}

}