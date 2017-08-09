#include "Scene.h"
#include "SceneManager.h"
#include "Engine.h"

namespace Ablaze
{

	Scene::Scene(const String& name)
		: name(name)
	{
		gameObjects = new GameObject*[AblazeEngine::maxEntities];
		SceneManager::SetCurrentScene(this);
	}

	Scene::~Scene()
	{
		for (auto layer : layers)
		{
			delete layer;
		}
	}

	uint Scene::GetHightestID() const
	{
		return highestID;
	}

	GameObject* Scene::Anchor() const
	{
		return anchorObject;
	}

	GameObject* Scene::GetAtID(uint id) const
	{
		return gameObjects[id];
	}

	bool Scene::IsValid(uint id) const
	{
		return gameObjects[id] != nullptr;
	}

	Layer* Scene::CurrentLayer() const
	{
		return currentLayer;
	}

	Layer* Scene::GetLayer(int index) const
	{
		return layers[index];
	}

	const String& Scene::GetName() const
	{
		return name;
	}

	int Scene::GetLayerCount() const
	{
		return layers.size();
	}

	void Scene::PushLayer(Layer* layer)
	{
		layers.push_back(layer);
		if (layers.size() == 1)
		{
			Initialise();
		}
		SetCurrentLayer(layer);
	}

	void Scene::RemoveLayer(Layer* layer)
	{
		auto it = std::find(layers.begin(), layers.end(), layer);
		layers.erase(it);
	}

	Layer* Scene::PopLayer()
	{
		Layer* l = layers.back();
		RemoveLayer(l);
		return l;
	}

	void Scene::SetCurrentLayer(int index)
	{
		SetCurrentLayer(layers[index]);
	}

	void Scene::SetCurrentLayer(Layer* layer)
	{
		currentLayer = layer;
	}

	void Scene::Render() const
	{
		for (int i = 0; i < GetLayerCount(); i++)
		{
			RenderLayer(i);
		}
	}

	void Scene::RenderLayer(int index) const
	{
		RenderLayerInternal(layers[index]);
	}

	void Scene::RenderLayerInternal(Layer* layer) const
	{
		layer->Render();
	}

	uint Scene::GetNextID()
	{
		for (uint i = 0; i < highestID + 5; i++)
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

	void Scene::Initialise()
	{
		for (uint i = 0; i < AblazeEngine::maxEntities; i++)
		{
			gameObjects[i] = nullptr;
		}
		anchorObject = new GameObject(true);
	}

}