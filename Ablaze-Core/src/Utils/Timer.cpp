#include "Timer.h"

namespace Ablaze
{

	Timer::Timer(double seconds)
	{
		goalTime = seconds;
		startTime = Time::TotalTime();
	}

	bool Timer::Check()
	{
		if (Time::TotalTime() - startTime >= goalTime)
		{
			startTime = Time::TotalTime();
			return true;
		}
		return false;
	}

	double Timer::GetGoalTime() const
	{
		return goalTime;
	}

	void Timer::SetGoalTime(double seconds)
	{
		goalTime = seconds;
	}

}