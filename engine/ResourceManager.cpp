#include "ResourceManager.h"
#include <fstream>
#include "LogManager.h"

using namespace df;

ResourceManager::ResourceManager()
{
	setType("ResourceManager");
}

ResourceManager::~ResourceManager()
{

}

ResourceManager& ResourceManager::GetInstance()
{
	static ResourceManager rm;
	return rm;
}

int ResourceManager::startUp()
{
	if (!LM.isStarted())
	{
		if (LM.startUp() == -1)
			return -1;
	}

	sprites_map.reserve(MAX_SPRITES);
	LM.writeLog("ResourceManager::startUp::Successfully started the ResourceManager.");
	return Manager::startUp();
}

void ResourceManager::shutDown()
{
	//clean up we're storing pointers so we need to manually delete
	for (auto pair : sprites_map) {
		if(pair.second != NULL)
			delete pair.second;
		pair.second = NULL;
	}

	for (auto pair : sounds_map) {
		if (pair.second != NULL)
			delete pair.second;
		pair.second = NULL;
	}

	for (auto pair : musics_map) {
		if (pair.second != NULL)
			delete pair.second;
		pair.second = NULL;
	}

	sounds_map.clear();
	sprites_map.clear();
	musics_map.clear();
	sound_count = 0;
	sprite_count = 0;
	music_count = 0;
	LM.writeLog("ResourceManager::shutDown::Successfully shutdown the ResourceManager.");
	Manager::shutDown();
}

int ResourceManager::loadSprite(std::string filename, std::string label)
{
	if (sprite_count == MAX_SPRITES)
	{
		LM.writeLog("ResourceManager::loadSprite::Failed to add sprite file with label %s, max sprite limit reached.", label.c_str());
		return -1;
	}
	//first attempt to open file
	std::string full_relative_path = SPRITE_FILE_DIRECTORY + filename;
	std::ifstream sprite_file(full_relative_path);
	if (!sprite_file.is_open())
	{
		LM.writeLog("ResourceManager::loadSprite::Failed to locate sprite file in assets folder with name %s.", filename.c_str());
		return -1;
	}
	std::string current_line;
	int frame_count = 0;
	int width = 0;
	int height = 0;
	int slowdown = 0;
	std::string color_name;
	//read from header first

	if (parseSpriteFileLine(&sprite_file, frame_count, "frame_count") == -1 ||
		parseSpriteFileLine(&sprite_file, width, "width") == -1 ||
		parseSpriteFileLine(&sprite_file, height, "height") == -1 ||
		parseSpriteFileLine(&sprite_file, slowdown, "slowdown") == -1 ||
		parseSpriteFileLine(&sprite_file, color_name, "color") == -1)
	{
		sprite_file.close();
		return -1;
	}



	Sprite* s = new Sprite(frame_count);
	s->setHeight(height);
	s->setWidth(width);
	s->setLabel(label);
	s->setSlowdown(slowdown);
	s->setColor(Color::colorFromString(color_name));

	//should have number of lines equal to frames
	for (int i = 0; i < frame_count; i++)
	{
		std::string frame_string = "";
		//space before each frame
		if (!std::getline(sprite_file, current_line))
		{
			LM.writeLog("ResourceManager::loadSprite::Frame formatting issue on frame: %d.", i);
			sprite_file.close();
			delete s;
			return -1;
		}

		for (int j = 0; j < height; j++)
		{
			if (std::getline(sprite_file, current_line))
			{
				if(current_line.size() == width)
					frame_string += current_line;
				else
				{
					LM.writeLog("ResourceManager::loadSprite::Frame formatting issue on frame: %d and line: %d, expected width of: %d, but got width of: %d.", i, j, width, current_line.size());
					delete s;
					sprite_file.close();
					return -1;
				}
			}			
			else
			{
				LM.writeLog("ResourceManager::loadSprite::Frame formatting issue on frame: %d and line: %d.", i, j);
				sprite_file.close();
				delete s;
				return -1;
			}
		}

		Frame f(width, height, frame_string);
		s->addFrame(f);
		sprite_count++;
	}

	if (std::getline(sprite_file, current_line)) //data beyond expected, through error
	{
		LM.writeLog("ResourceManager::loadSprite::Frame formatting issue, more data past expect amount of frames.");
		sprite_file.close();
		delete s;
		return -1;
	}


	//if we got this far everything worked
	if(sprites_map.find(label) == sprites_map.end())
		sprites_map[label] = s;
	else
	{
		LM.writeLog("ResourceManager::loadSprite::The label of %s was already found in sprite_map, faliure to add.", label.c_str());
		sprite_file.close();
		delete s;
		return -1;
	}
	sprite_file.close();
	LM.writeLog("ResourceManager::loadSprite::Sprite with label: %s, successfully loaded.", label.c_str());
	return 0;
}

int ResourceManager::unloadSprite(std::string label)
{
	if (sprites_map.find(label) == sprites_map.end()) //can't unload non-existent sprite
	{
		LM.writeLog("ResourceManager::unloadSprite::Sprite with label: %s, faliure to unload, doesn't exist.", label.c_str());
		return -1;
	}

	Sprite* sprite = sprites_map[label];
	delete sprite;
	sprite = NULL;
	sprites_map.erase(label);
	sprite_count--;
	return 0;
}

Sprite* ResourceManager::getSprite(std::string label) const
{
	if (sprites_map.find(label) == sprites_map.end()) //can't unload non-existent sprite
	{
		LM.writeLog("ResourceManager::getSprite::Sprite with label: %s, faliure to get, doesn't exist.", label.c_str());
		return NULL;
	}

	return sprites_map.at(label);
}

int ResourceManager::parseSpriteFileLine(std::ifstream* file, int& value, std::string header_info_name)
{
	std::string line;
	if (!std::getline(*file, line))
	{
		LM.writeLog("ResourceManager::loadSprite::Failed with header attribute: %s.", header_info_name.c_str());
		return -1;
	}

	try { value  = std::stoi(line); }
	catch (...) {
		LM.writeLog("ResourceManager::loadSprite::Failed with header attribute: frame count, it must be an integer!.");
		return -1;
	}
	return 0;
}

int ResourceManager::parseSpriteFileLine(std::ifstream* file, std::string& value, std::string info_name)
{
	if (!std::getline(*file, value))
	{
		LM.writeLog("ResourceManager::loadSprite::Failed with attribute: %s.", info_name.c_str());
		return -1;
	}
	return 0;
}

int ResourceManager::loadSound(std::string filename, std::string label)
{
	if (sound_count == MAX_SOUNDS)
	{
		LM.writeLog("ResourceManager::loadSound::Failed to add sound file with label %s, max sound limit reached.", label.c_str());
		return -1;
	}
	Sound* s = new Sound();
	if (s->loadSound(filename) == -1) //sound already has logging
	{ 
		delete s;
		return -1;
	}
	s->setLabel(label);
	if (sounds_map.find(label) != sounds_map.end())
	{
		LM.writeLog("ResourceManager::loadSound::Failed with label: %s because label wasalready in the sounds_map.", label.c_str());
		delete s;
		return -1;
	}
	sounds_map[label] = s;
	sound_count++;
	return 0;
}

int ResourceManager::unloadSound(std::string label)
{
	if (sounds_map.find(label) == sounds_map.end()) //can't unload non-existent sound
	{
		LM.writeLog("ResourceManager::unloadSound::Sound with label: %s, faliure to unload, doesn't exist.", label.c_str());
		return -1;
	}

	Sound* s = sounds_map[label];
	delete s;
	s = NULL;
	sounds_map.erase(label);
	sound_count--;
	return 0;
}

Sound* ResourceManager::getSound(std::string label) const
{
	if (sounds_map.find(label) == sounds_map.end()) //can't unload non-existent sound
	{
		LM.writeLog("ResourceManager::getSound::Sound with label: %s, faliure to get, doesn't exist.", label.c_str());
		return NULL;
	}
	return sounds_map.at(label);
}

int ResourceManager::loadMusic(std::string filename, std::string label)
{
	if (music_count == MAX_MUSICS)
	{
		LM.writeLog("ResourceManager::loadMusic::Failed to add music file with label %s, max music limit reached.", label.c_str());
		return -1;
	}
	Music* m = new Music();
	if (m->loadMusic(filename) == -1) //music already has logging
	{
		delete m;
		return -1;
	}
	m->setLabel(label);
	if (musics_map.find(label) != musics_map.end())
	{
		LM.writeLog("ResourceManager::loadMusic::Failed with label: %s because label was already in the musics_map.", label.c_str());
		delete m;
		return -1;
	}
	musics_map[label] = m;
	music_count++;
	return 0;
}

int ResourceManager::unloadMusic(std::string label)
{
	if (musics_map.find(label) == musics_map.end()) //can't unload non-existent music
	{
		LM.writeLog("ResourceManager::unloadMusic::Music with label: %s, faliure to unload, doesn't exist.", label.c_str());
		return -1;
	}

	Music* m = musics_map[label];
	//delete m;
	//m = NULL;
	musics_map.erase(label);
	music_count--;
	return 0;
}

Music* ResourceManager::getMusic(std::string label) const
{
	if (musics_map.find(label) == musics_map.end()) //can't unload non-existent music
	{
		LM.writeLog("ResourceManager::getMusic::Music with label: %s, faliure to get, doesn't exist.", label.c_str());
		return NULL;
	}
	return musics_map.at(label);
}