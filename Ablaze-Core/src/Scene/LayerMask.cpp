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
	
	}

	LayerMask::LayerMask(const String& layer0, const String& layer1) : LayerMask(SceneManager::CurrentScene()->MaskOf(layer0) | SceneManager::CurrentScene()->MaskOf(layer1))
	{

	}

	LayerMask::LayerMask(const String& layer0, const String& layer1, const String& layer2) : LayerMask(SceneManager::CurrentScene()->MaskOf(layer0) | SceneManager::CurrentScene()->MaskOf(layer1) | SceneManager::CurrentScene()->MaskOf(layer2))
	{

	}

	void LayerMask::AddLayer(const String& layer)
	{
		mask |= SceneManager::CurrentScene()->MaskOf(layer);
	}

	void LayerMask::AddLayer(Layer* layer)
	{
		mask |= SceneManager::CurrentScene()->MaskOf(layer);
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