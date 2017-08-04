#include "Application.h"
#include "Engine.h"
#include "Log.h"

namespace Ablaze
{

	Application::Application()
	{
		window = nullptr;
		prevTime = glfwGetTime();
		tickPrevTime = prevTime;

		//glfwSetErrorCallback(ErrorCallback);
		if (!glfwInit())
		{
			AB_FATAL("Unable to initialise GLFW");
		}
	}

	Application::~Application()
	{
		delete window;
	}

	Window* Application::BuildWindow(int width, int height, const String& title, const Color& clearColor)
	{
		window = new Window(width, height, title, clearColor);
		AblazeEngine::Init();
		return window;
	}

	Window* Application::WindowHandle()
	{
		return window;
	}

	int Application::WindowWidth()
	{
		return window->GetWidth();
	}

	int Application::WindowHeight()
	{
		return window->GetHeight();
	}

	void Application::Start()
	{
		PushSystem(new UpdateSytem());
		PushSystem(new LightingSystem());
		PushSystem(new PhysicsSystem());
		Run();
	}

	void Application::PushSystem(System* system)
	{
		SystemManager::PushSystem(system);
	}

	void Application::PushScene(Scene* scene)
	{
		scenes.push_front(scene);
	}

	void Application::Run()
	{
		Init();
		if (window == nullptr)
		{
			AB_FATAL("Window was not initialised in Init() method");
			return;
		}			
		
		Time::Reset();
		while (!window->ShouldClose())
		{
			double current = glfwGetTime();
			if (current - tickPrevTime >= 1.0)
			{
				Tick();
				tickPrevTime = current;
			}
			if (current - prevTime >= updateTick)
			{
				Update();
				prevTime = current;
			}
			Render();
		}
		AblazeEngine::Terminate();
		return;
	}

	void Application::Tick()
	{
	
	}

	void Application::Update()
	{
		Time::OnUpdate();
		if (GameObject::GetHightestID() > 0)
			SystemManager::Run();
	}

	void Application::Render()
	{
		window->Update();
		Time::OnRender();
		for (auto scene : scenes)
		{
			scene->Render();
		}
		window->SwapBuffers();
	}

}