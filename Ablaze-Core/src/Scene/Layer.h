#pragma once
#include "RenderEngine/Interfaces/Renderer.h"
#include "Graphics/Resources/Shaders/Shader.h"
#include "Entities/GameObject.h"
#include "Graphics/Resources/Imaging/Framebuffers/Framebuffer.h"

namespace Ablaze
{

	class Layer
	{
	protected:
		Renderer* renderer;
		GameObject* camera;
		String name;
		std::vector<GameObject*> gameObjects;
		Framebuffer* defaultRenderTarget;

	public:
		Layer(String name, Renderer* renderer);
		virtual ~Layer();

		Renderer* GetRenderer() const;
		GameObject* GetCamera() const;
		const String& GetName() const;
		bool HasCamera() const;
		Framebuffer* GetRenderTarget() const;

		void SetAsCurrent();
		void SetCamera(GameObject* camera);
		void SetRenderer(Renderer* renderer);
		void SetName(const String& name);
		void SetRenderTarget(Framebuffer* renderTarget);

		void AddGameObject(GameObject* const obj);
		void RemoveGameObject(GameObject* const obj);

		virtual void Render(Framebuffer* renderTarget = nullptr);

	};

}