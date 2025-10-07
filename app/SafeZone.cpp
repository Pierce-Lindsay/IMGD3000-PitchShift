#include "SafeZone.h"
#include "../engine/LogManager.h"

SafeZone::SafeZone(std::vector<float>& safePositions, float positionSpacingSeconds, df::Music* music) : safePositions(safePositions), positionSpacingSeconds(positionSpacingSeconds), music(music)
{
	size = safePositions.size();
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

	if(upper_index >= size) {
		finished = true;
		LM.GetInstance().writeLog("SafeZone::getSafeZone: Safe zone finished, returning -1.");
		return -1; //no safe zone
	}

	float lower_val = safePositions[lower_index];
	float upper_val = safePositions[upper_index];
	float t = (current_position_sec - (lower_index * positionSpacingSeconds)) / positionSpacingSeconds;
	return lerp(lower_val, upper_val, t); //linear interpolation between the two positions
}

void SafeZone::start()
{
	if (music == nullptr)
	{
		LM.writeLog("SafeZone::start: Warning! No music provided, cannot start safe zone.");
		return;
	}
	music->play();
	started = true;
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
	if(started && music->getMusic()->getStatus() != sf::SoundSource::Status::Playing)
		finished = true;
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