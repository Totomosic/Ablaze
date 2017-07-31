#pragma once
#include "Graphics\Context.h"
#include "Debug\Timer.h"
#include "Entities\Entities.h"
#include "Scene\Scene.h"
#include "Types.h"
#include <deque>

namespace Ablaze
{

	class Application
	{
	private:
		// Timing variables
		double prevTime;
		double tickPrevTime;
		const double updateTick = 1.0 / 60.0;

	protected:
		Window* window;
		std::deque<Scene*> scenes;

	public:
		Application();
		virtual ~Application();

		Window* BuildWindow(int width, int height, const String& title, const Color& clearColor = Color::Black());
		Window* WindowHandle();
		int WindowWidth();
		int WindowHeight();

		void Start();
		void PushSystem(System* system);
		void PushScene(Scene* scene);

		virtual void Init() = 0; // Called once
		virtual void Tick(); // Called once per second
		virtual void Update(); // Called 60 times per second
		virtual void Render(); // Called as often as possible

	private:
		void Run();

	};

}