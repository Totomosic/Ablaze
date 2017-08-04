#pragma once
#include <random>
#include <ctime>

namespace Ablaze
{

	class Random
	{
	private:
		static std::minstd_rand gen;

		Random() { }

	public:
		static void Initialise();

		static int NextInt(int low, int high);
		static float NextFloat(float low, float high);
		static float NextFloat();
	};

}