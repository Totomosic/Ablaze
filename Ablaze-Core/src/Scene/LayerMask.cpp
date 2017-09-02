#include "LayerMask.h"
#include "Scene/SceneManager.h"

namespace Ablaze
{

	LayerMask::LayerMask() : LayerMask(0)
	{
	
	}

	LayerMask::LayerMask(int64 mask)
		: mask(mask)
	{

	}

	LayerMask::LayerMask(const String& layer) : LayerMask(SceneManager::CurrentScene()->MaskOf(layer))
	{
		layers.push_back(layer);
	}

	LayerMask::LayerMask(const String& layer0, const String& layer1) : LayerMask(SceneManager::CurrentScene()->MaskOf(layer0) | SceneManager::CurrentScene()->MaskOf(layer1))
	{
		layers.push_back(layer0);
		layers.push_back(layer1);
	}

	LayerMask::LayerMask(const String& layer0, const String& layer1, const String& layer2) : LayerMask(SceneManager::CurrentScene()->MaskOf(layer0) | SceneManager::CurrentScene()->MaskOf(layer1) | SceneManager::CurrentScene()->MaskOf(layer2))
	{
		layers.push_back(layer0);
		layers.push_back(layer1);
		layers.push_back(layer2);
	}

	void LayerMask::AddLayer(const String& layer)
	{
		mask |= SceneManager::CurrentScene()->MaskOf(layer);
		layers.push_back(layer);
	}

	void LayerMask::AddLayer(Layer* layer)
	{
		mask |= SceneManager::CurrentScene()->MaskOf(layer);
		layers.push_back(layer->GetName());
	}

	void LayerMask::Evaluate()
	{
		mask = 0;
		for (auto layerName : layers)
		{
			mask |= SceneManager::CurrentScene()->MaskOf(layerName);
		}
	}

	LayerMask LayerMask::All()
	{
		LayerMask l;
		for (int i = 0; i < SceneManager::CurrentScene()->GetLayerCount(); i++)
		{
			l.mask |= SceneManager::CurrentScene()->MaskOf(SceneManager::CurrentScene()->GetLayer(i));
		}
		return l;
	}

}