#include "Scene.h"
#include "SceneManager.h"

namespace Ablaze
{

	Scene::Scene(const String& name)
		: name(name)
	{
		SceneManager::SetCurrentScene(this);
	}

	Scene::~Scene()
	{
		for (auto layer : layers)
		{
			delete layer;
		}
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

}