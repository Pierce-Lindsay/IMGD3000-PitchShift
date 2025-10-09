#include "SafeZone.h"
#include "../engine/LogManager.h"
#include "../engine/game/worldManager.h"
#include "Player.h"
#include "EventLevelUp.h"
#include <iostream>

SafeZone::SafeZone(std::vector<float>& safePositions, float positionSpacingSeconds, df::Music* music) : safePositions(safePositions), positionSpacingSeconds(positionSpacingSeconds), music(music)
{
}

float SafeZone::getSafeZone()
{
	if (finished)
	{
		LM.GetInstance().writeLog("SafeZone::getSafeZone: Warning! Safe zone already finished, returning -1.");
		return -1; //no safe zone
	}

	float current_position_sec = music->getMusic()->getPlayingOffset().asMilliseconds()/1000.0f;
	//interpolate between positions
	int lower_index = (int)floor((current_position_sec / positionSpacingSeconds));
	int upper_index = (int)ceil((current_position_sec / positionSpacingSeconds));

	//clamp if neccessary
	if (upper_index >= safePositions.size())
		upper_index = safePositions.size()-1;

	if (lower_index >= safePositions.size() - 1)
		lower_index = safePositions.size() - 2; 

	float lower_val = safePositions[lower_index];
	float upper_val = safePositions[upper_index];
	float t = (current_position_sec - (lower_index * positionSpacingSeconds)) / positionSpacingSeconds; //find aplha between the two positions
	return lerp(lower_val, upper_val, t); //linear interpolation between the two positions
}

int SafeZone::getSafeZoneDeltaDirection()
{
	float current_position_sec = music->getMusic()->getPlayingOffset().asMilliseconds() / 1000.0f;
	//interpolate between positions
	int lower_index = (int)floor((current_position_sec / positionSpacingSeconds));
	int upper_index = (int)ceil((current_position_sec / positionSpacingSeconds));

	//clamp if neccessary
	if (upper_index >= safePositions.size())
		upper_index = safePositions.size() - 1;

	if (lower_index >= safePositions.size() - 1)
		lower_index = safePositions.size() - 2;

	if (safePositions[upper_index] - safePositions[lower_index] < 0)
	{
		return -1;
	}
	return 1;
}

void SafeZone::start()
{
	if (music == nullptr)
	{
		LM.writeLog("SafeZone::start: Warning! No music provided, cannot start safe zone.");
		return;
	}
	music->play(true); //keeping looping
	started = true;
	clock.delta(); //reset clock
}

bool SafeZone::isFinished() const
{
	return finished;
}

bool SafeZone::hasStarted() const
{
	return started;
}

void SafeZone::update()
{
	if (started && music->getMusic()->getStatus() != sf::SoundSource::Status::Playing)
	{
		finished = true;
		std::cout << "finished safe zone" << std::endl;
		return;
	}
	long long time_passed = clock.split() / 1000;
	//std::cout << "time passed: " << time_passed << " ms, width: " << width << std::endl;
	if (time_passed >= LEVEL_UP_TIME)
	{
		if(width > DEFAULT_MIN_SAFE_ZONE_WIDTH)
			width -= LEVEL_UP_DECREASE; //decrease width every level if greater than min
		clock.delta(); //reset clock
		level++;
		EventLevelUp e(level);
		WM.onEvent(&e);
	}
		
}

float SafeZone::getWidth() const
{
	return width;
}

void SafeZone::setWidth(float width)
{
	this->width = width;
}

float SafeZone::lerp(float a, float b, float t)
{
	return a + t * (b - a);
}

float SafeZone::getMusicTime() const
{
	if (music == NULL || finished || !started)
		return 0;
	return music->getMusic()->getPlayingOffset().asMilliseconds();
}


void SafeZone::stopMusic()
{
	if (music != NULL)
		music->stop();
}