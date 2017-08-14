#include "Scene.h"
#include "SceneManager.h"
#include "Engine.h"
#include "RenderEngine/structs/Commands/Commands.h"
#include "Graphics/Context.h"

namespace Ablaze
{

	Scene::Scene(const String& name)
		: name(name)
	{
		gameObjects = new GameObject*[AblazeEngine::maxEntities];
		SceneManager::SetCurrentScene(this);
		renderer = new CommandQueue();
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

	int Scene::IndexOf(const String& layerName) const
	{
		for (int i = 0; i < GetLayerCount(); i++)
		{
			if (layers[i]->GetName() == layerName)
				return i;
		}
		return -1;
	}

	int Scene::IndexOf(Layer* layer) const
	{
		return std::distance(layers.begin(), std::find(layers.begin(), layers.end(), layer));
	}

	int64 Scene::MaskOf(const String& layerName) const
	{
		return (int64)pow(2, IndexOf(layerName));
	}

	int64 Scene::MaskOf(Layer* layer) const
	{
		return (int64)pow(2, IndexOf(layer));
	}

	int Scene::GetLayerCount() const
	{
		return layers.size();
	}

	std::vector<Layer*> Scene::GetLayers(int64 mask) const
	{
		std::vector<Layer*> layersFound;
		for (int i = 0; i < GetLayerCount(); i++)
		{
			int64 m = (int64)pow(2, i);
			if ((mask & m) == m)
			{
				layersFound.push_back(layers[i]);
			}
		}
		if (layersFound.size() == 0)
		{
			AB_ERROR("No layers found");
		}
		return layersFound;
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
		renderer->PushCommand(new RTSwapCommand(Context::Window()->GetFramebuffer()));
		renderer->Execute(maths::mat4::Identity(), maths::mat4::Identity());
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