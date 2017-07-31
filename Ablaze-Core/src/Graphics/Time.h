#pragma once
#include "AblazeGL.h"
#include "Types.h"

namespace Ablaze
{

	class Time
	{
	private:
		static double updatePrevTime;
		static double updateElapsedSeconds;

		static double renderPrevTime;
		static double renderElapsedSeconds;

		static std::vector<int> fpss;
		static int avgFPS;

	public:
		static double Elapsed();
		static double DeltaTime();
		static double RenderElapsed();

		static int UpdatesPerSecond();
		static int FramesPerSecond();
		static int AverageFPS();
		static double TotalTime();

		static void Reset();

		static void OnUpdate();
		static void OnRender();

	private:
		static double AverageVector(const std::vector<int>& fps);

	};

}