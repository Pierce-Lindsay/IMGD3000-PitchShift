#include "Clock.h"
#include <chrono>
using namespace df;
Clock::Clock()
{
	start = std::chrono::high_resolution_clock::now();
}

long long Clock::delta()
{
	//set previous time
	auto stop = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
	start = stop;
	return duration.count();
}

long long Clock::split() const
{
	auto now = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(now - start);
	return duration.count();
}