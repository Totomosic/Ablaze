#include "Layer.h"
#include "Entities/Components/Components.h"
#include "Entities/Camera.h"
#include "RenderEngine/structs/Commands/Commands.h"
#include "Graphics/Context.h"
#include "SceneManager.h"

namespace Ablaze
{

	Layer::Layer(String name, Renderer* renderer)
		: name(name), renderer(renderer), camera(nullptr)
	{
		SceneManager::CurrentScene()->PushLayer(this);
	}

	Layer::~Layer()
	{
		delete renderer;
	}

	Renderer* Layer::GetRenderer() const
	{
		return renderer;
	}

	GameObject* Layer::GetCamera() const
	{
		return camera;
	}

	const String& Layer::GetName() const
	{
		return name;
	}

	void Layer::SetCamera(GameObject* camera)
	{
		this->camera = camera;
	}

	void Layer::SetName(const String& name)
	{
		this->name = name;
	}

	void Layer::SetRenderer(Renderer* renderer)
	{
		this->renderer = renderer;
	}

	void Layer::AddGameObject(GameObject* const obj)
	{
		gameObjects.push_back(obj);
	}

	void Layer::RemoveGameObject(GameObject* const obj)
	{
		auto it = std::find(gameObjects.begin(), gameObjects.end(), obj);
		if (it != gameObjects.end())
		{
			gameObjects.erase(it);
		}
	}

	void Layer::Render()
	{
		std::vector<Renderable*> renderables;
		Components::Camera* cam = camera->GetComponent<Components::Camera>();
		Components::Transform* t = camera->Transform();
		renderer->PushCommand(new ClearCommand(Context::Window()->GetFramebuffer()));

		// Sort gameObjects
		std::sort(gameObjects.begin(), gameObjects.end(), [t](GameObject* a, GameObject* b) {
			return ((a->Transform()->GetNievePosition() - t->GetNievePosition()).GetLengthSqrd() < (b->Transform()->GetNievePosition() - t->GetNievePosition()).GetLengthSqrd());
		});

		for (auto obj : gameObjects)
		{
			if (!obj->HasComponent<Components::Transform>() || !obj->HasComponent<Components::MeshComponent>())
			{
				continue;
			}
			Components::Transform* transform = obj->GetComponent<Components::Transform>();
			Components::MeshComponent* mesh = obj->GetComponent<Components::MeshComponent>();

			Renderable* renderable = new Renderable(mesh->GetMesh(), transform->GetModelMatrix());
			renderer->PushCommand(new RenderCommand(renderable));
			renderables.push_back(renderable);
		}
		renderer->PushCommand(new RTSwapCommand(Context::Window()->GetFramebuffer()));
		renderer->Execute(cam->GetViewMatrix(), cam->GetProjectionMatrix());

		for (auto renderable : renderables)
		{
			delete renderable;
		}
	}

}