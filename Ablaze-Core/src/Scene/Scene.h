#pragma once
#include "Layer.h"
#include "Types.h"

#include "Scene\Physics\Physics.h"
#include "Terrain\Terrain.h"
#include "Terrain\HeightFunctions\PerlinNoise.h"

namespace Ablaze
{

	class Scene
	{
	private:
		String name;
		std::vector<Layer*> layers;

	public:
		Scene(const String& name);
		~Scene();

		Layer* GetLayer(int index = 0) const;
		const String& GetName() const;
		int GetLayerCount() const;

		void SetCurrentLayer(int index) const;
		void PushLayer(Layer* layer);
		Layer* PopLayer();

		void Render() const;
		void RenderLayer(int index) const;

	private:
		void RenderLayerInternal(Layer* layer) const;

	};

}