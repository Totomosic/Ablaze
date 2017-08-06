#pragma once
#include "RenderEngine/Interfaces/Renderer.h"
#include "Graphics/Shaders/Shader.h"
#include "Entities/GameObject.h"

namespace Ablaze
{

	class Layer
	{
	private:
		static Layer* currentLayer;

	protected:
		Renderer* renderer;
		GameObject* camera;
		String name;
		std::vector<GameObject*> gameObjects;

	public:
		Layer(String name, Renderer* renderer, GameObject* camera);
		virtual ~Layer();

		Renderer* GetRenderer() const;
		GameObject* GetCamera() const;
		String GetName() const;

		void SetCamera(GameObject* camera);
		void SetRenderer(Renderer* renderer);
		void SetName(String name);
		void AddGameObject(GameObject* const obj);
		void RemoveGameObject(GameObject* const obj);

		virtual void Render();

		static Layer* GetCurrentLayer();
		static void SetCurrentLayer(Layer* layer);

	};

}