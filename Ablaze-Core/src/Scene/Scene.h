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
		GameObject** gameObjects;
		uint highestID;
		GameObject* anchorObject; // All GameObjects are children of anchor, most of the time will be positioned at (0, 0, 0)

	private:
		String name;
		std::vector<Layer*> layers;
		Layer* currentLayer;

	public:
		Scene(const String& name);
		~Scene();

		GameObject* Anchor() const;
		uint GetHightestID() const;
		GameObject* GetAtID(uint id) const;
		bool IsValid(uint id) const;
		void DestroyAll();

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

		friend class GameObject;

	private:
		void RenderLayerInternal(Layer* layer) const;
		uint GetNextID();
		void Initialise();

	};

}