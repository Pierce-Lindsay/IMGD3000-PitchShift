#include "Music.h"
#include "../LogManager.h"

using namespace df;

Music::Music()
{

}

Music::~Music()
{
	music.stop();
	LM.writeLog("Music::~Music::Destructed music with label: %s", label.c_str());
}

int Music::loadMusic(std::string filename)
{
	std::string path = MUSIC_FILE_DIRECTORY + filename;
	if (!music.openFromFile(path))
	{
		LM.writeLog("Music::loadMusic::Failed to load music in assets/music/ with name: %s ", filename.c_str());
		return -1;
	}
	valid = true;
	return 0;
}

void Music::setLabel(std::string label)
{
	this->label = label;
}

std::string Music::getLabel() const
{
	return label;
}

void Music::play(bool loop)
{
	if (!valid)
	{
		LM.writeLog("Music::play::Tried to play invalid music with label: %s", label.c_str());
		return;
	}
	music.setLooping(loop);
	music.play();
}

void Music::stop()
{
	if (!valid)
	{
		LM.writeLog("Music::stop::Tried to stop invalid music with label: %s", label.c_str());
		return;
	}
	music.stop();
}

void Music::pause()
{
	if (!valid)
	{
		LM.writeLog("Music::pause::Tried to pause invalid music with label: %s", label.c_str());
		return;
	}
	music.pause();
}

sf::Music* Music::getMusic()
{
	return &music;
}