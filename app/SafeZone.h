#pragma once
#include <vector>

/// <summary>
/// 
/// </summary>
class SafeZone
{
private:
	int size = 0; // 1/2 second positions
	std::vector<float>& safePositions;
public:
	float getSafeZone(float time_passed_seconds);
	SafeZone(std::vector<float>& safePositions);
};