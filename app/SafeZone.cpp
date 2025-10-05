#include "SafeZone.h"

SafeZone::SafeZone(std::vector<float>& safePositions) : safePositions(safePositions)
{
	size = safePositions.size();
}

float SafeZone::getSafeZone(float time_passed_seconds)
{
	return 0;
}