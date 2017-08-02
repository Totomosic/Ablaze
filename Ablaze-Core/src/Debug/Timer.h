#pragma once
#include "Graphics/Time.h"

namespace Ablaze
{

	class Timer
	{
	private:
		double startTime;
		double goalTime;

	public:
		Timer(double endTimeSeconds);

		bool Check();
		double GetGoalTime() const;
		void SetGoalTime(double seconds);

	};

}