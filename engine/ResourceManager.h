#pragma once
#include "Manager.h"
#include "graphics/Sprite.h"
#include "audio/Music.h"	
#include "audio/Sound.h"
#include <unordered_map>
#include <string>
#include <vector>
#include <fstream>

#define RM df::ResourceManager::GetInstance()

namespace df
{
	const int MAX_SPRITES = 500;
	const int MAX_SOUNDS = 500;
	const int MAX_MUSICS = 500;
	const std::string SPRITE_FILE_DIRECTORY = "assets/sprites/";

	/// <summary>
	/// Call for handling the resources of the engine (sprites, audio, music etc.).
	/// </summary>
	class ResourceManager : public Manager
	{
	private:
		//singleton stuff
		ResourceManager();
		ResourceManager(ResourceManager const& copy);
		void operator=(ResourceManager const& assign);
		std::unordered_map<std::string, Sprite*> sprites_map; //hashmap of sprites loaded
		std::unordered_map<std::string, Sound*> sounds_map; //hashmap of sounds loaded
		std::unordered_map<std::string, Music*> musics_map; //hashmap of musics loaded
		int sprite_count = 0; //current count of sprites
		int sound_count = 0;//current count of sounds
		int music_count = 0;//current count of musics

		/// <summary>
		/// Parse a int line from the given file, passing the int into the given value. 
		/// Throws error with the given header_info_name if neccessary.
		/// </summary>
		/// <returns>-1 if no line to get or not int, 0 if ok.</returns>
		int parseSpriteFileLine(std::ifstream* file, int& value, std::string header_info_name);

		/// <summary>
		/// Parse a string line from the given file, passing the string into the given value.
		/// Throws error with the given info_name if neccessary.
		/// </summary>
		/// <returns>-1 if no line to get, 0 if ok.</returns>
		int parseSpriteFileLine(std::ifstream* file, std::string& value, std::string info_name);

	public:
		/// <summary>
		/// Destroys the resource manager and any other dependencies.
		/// </summary>
		~ResourceManager();

		/// <summary>
		/// Get instance of the one and only ResourceManager.
		/// </summary>
		/// <returns></returns>
		static ResourceManager& GetInstance();

		/// <summary>
		/// Start up ResourceManager and required dependencies.
		/// </summary>
		/// <returns>0 if successful.</returns>
		int startUp() override;

		/// <summary>
		/// Shut down ResourceManager and required dependencies. 
		/// </summary>
		void shutDown() override;

		/// <summary>
		/// Loads the sprite with the given file name and gives it the label. Adds it to the sprite map.
		/// The expected file path provided by filename is relative to the ../assets/sprites folder.
		/// </summary>
		/// <returns>0 if loaded and added successfully, -1 else.</returns>
		int loadSprite(std::string filename, std::string label);

		/// <summary>
		/// Removes the given sprite with the given label from the sprite map.
		/// </summary>
		/// <returns>0 if removed and deleted successfully, -1 else.</returns>
		int unloadSprite(std::string label);

		/// <summary>
		/// Get the sprite with the given label from the map, return NULL sprite if label not found.
		/// </summary>
		Sprite* getSprite(std::string label) const;

		/// <summary>
		/// Loads the sound with the given file name and gives it the label. Adds it to the sounds map.
		/// The expected file path provided by filename is relative to the ../assets/sounds folder.
		/// </summary>
		/// <returns>0 if loaded and added successfully, -1 else.</returns>
		int loadSound(std::string filename, std::string label);

		/// <summary>
		/// Removes the given sound with the given label from the sounds map.
		/// </summary>
		/// <returns>0 if removed and deleted successfully, -1 else.</returns>
		int unloadSound(std::string label);

		/// <summary>
		/// Get the sound with the given label from the map, return NULL sound if label not found.
		/// </summary>
		Sound* getSound(std::string label) const;

		/// <summary>
		/// Loads the music with the given file name and gives it the label. Adds it to the musics map.
		/// The expected file path provided by filename is relative to the ../assets/music folder.
		/// </summary>
		/// <returns>0 if loaded and added successfully, -1 else.</returns>
		int loadMusic(std::string filename, std::string label);

		/// <summary>
		/// Removes the given music with the given label from the musics map.
		/// </summary>
		/// <returns>0 if removed and deleted successfully, -1 else.</returns>
		int unloadMusic(std::string label);

		/// <summary>
		/// Get the music with the given label from the map, return NULL music if label not found.
		/// </summary>
		Music* getMusic(std::string label) const;
	};
}

