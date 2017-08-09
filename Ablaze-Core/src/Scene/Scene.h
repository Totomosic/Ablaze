#pragma once
#include "Layer.h"
#include "Types.h"

#include "Scene/Physics/Physics.h"
#include "Terrain/Terrain.h"
#include "Terrain/HeightFunctions/PerlinNoise.h"
#include "Terrain/HeightFunctions/HeightmapFunction.h"

namespace Ablaze
{

	class Scene
	{
	private:
		String name;
		std::vector<Layer*> layers;
		Layer* currentLayer;

	public:
		Scene(const String& name);
		~Scene();

		Layer* CurrentLayer() const;
		Layer* GetLayer(int index = 0) const;
		const String& GetName() const;
		int GetLayerCount() const;

		void SetCurrentLayer(int index);
		void SetCurrentLayer(Layer* layer);
		void PushLayer(Layer* layer);
		void RemoveLayer(Layer* layer);
		Layer* PopLayer();

		void Render() const;
		void RenderLayer(int index) const;

	private:
		void RenderLayerInternal(Layer* layer) const;

	};

}