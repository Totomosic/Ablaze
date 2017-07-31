#include "Time.h"

namespace Ablaze
{

	double Time::updateElapsedSeconds = 0.0;
	double Time::updatePrevTime = 0.0;
	double Time::renderElapsedSeconds = 0.0;
	double Time::renderPrevTime = 0.0;
	std::vector<int> Time::fpss = std::vector<int>();
	int Time::avgFPS = 60;

	void Time::OnUpdate()
	{
		double current = glfwGetTime();
		updateElapsedSeconds = current - updatePrevTime;
		updatePrevTime = current;
	}

	void Time::OnRender()
	{
		double renderCurrent = glfwGetTime();
		renderElapsedSeconds = renderCurrent - renderPrevTime;
		renderPrevTime = renderCurrent;
		fpss.push_back(1.0 / renderElapsedSeconds);
		if (fpss.size() >= 100)
		{
			avgFPS = (int)AverageVector(fpss);
			fpss.clear();
		}
	}

	double Time::Elapsed()
	{
		return updateElapsedSeconds;
	}

	double Time::DeltaTime()
	{
		return Elapsed();
	}

	double Time::RenderElapsed()
	{
		return renderElapsedSeconds;
	}

	double Time::TotalTime()
	{
		return glfwGetTime();
	}

	int Time::UpdatesPerSecond()
	{
		return (int)(1.0 / Elapsed());
	}

	int Time::FramesPerSecond()
	{
		return (int)(1.0 / RenderElapsed());
	}

	int Time::AverageFPS()
	{
		return avgFPS;
	}

	void Time::Reset()
	{
		updatePrevTime = glfwGetTime();
		updateElapsedSeconds = 0.0;
		renderPrevTime = updatePrevTime;
		renderElapsedSeconds = updateElapsedSeconds;
	}

	double Time::AverageVector(const std::vector<int>& fps)
	{
		double total = 0.0;
		for (int value : fps)
		{
			total += value;
		}
		total /= fps.size();
		return total;
	}

}