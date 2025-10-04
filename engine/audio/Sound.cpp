#include "Sound.h"
#include "../LogManager.h"

using namespace df;

Sound::Sound()
{

}

Sound::~Sound()
{
	if (sound != NULL)
		delete sound;
	sound = NULL;
	LM.writeLog("Sound::~Sound::Destructed sound with label: %s", label.c_str());
}

int Sound::loadSound(std::string filename)
{
	std::string path = SOUND_FILE_DIRECTORY + filename;
	if (!sound_buffer.loadFromFile(path))
	{
		LM.writeLog("Sound::loadSound::Failed to load sound in assets/sounds/ with name: %s ", filename.c_str());
		return -1;
	}
	sound = new sf::Sound(sound_buffer);
	return 0;
}

void Sound::setLabel(std::string label)
{
	this->label = label;
}

std::string Sound::getLabel() const
{
	return label;
}

void Sound::play(bool loop)
{
	if (sound == NULL)
	{
		LM.writeLog("Sound::play::Tried to play NULL sound with label: %s", label.c_str());
		return;
	}
	sound->setLooping(loop);
	sound->play();
}

void Sound::stop()
{
	if (sound == NULL)
	{
		LM.writeLog("Sound::stop::Tried to stop NULL sound with label: %s", label.c_str());
		return;
	}
	sound->stop();
}

void Sound::pause()
{
	if (sound == NULL)
	{
		LM.writeLog("Sound::pause::Tried to pause NULL sound with label: %s", label.c_str());
		return;
	}
	sound->pause();
}

sf::Sound* Sound::getSound() const
{
	return sound;
}