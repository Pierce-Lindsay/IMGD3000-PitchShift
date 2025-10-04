#pragma once
#include <string>
#include "SFML/Audio.hpp"

namespace df {

	const std::string SOUND_FILE_DIRECTORY = "assets/sounds/";
	/// <summary>
	/// Class for handling sounds and playing them.
	/// </summary>
	class Sound
	{
	private:
		sf::Sound* sound = NULL; //sfml sound pointer
		sf::SoundBuffer sound_buffer; //buffer to store sound data
		std::string label = "undefined"; //name of the sound

	public:
		/// <summary>
		/// Create default sound (no data).
		/// </summary>
		Sound();

		/// <summary>
		/// Destruct sound and handle dependencies.
		/// </summary>
		~Sound();

		/// <summary>
		/// Load the sound with the given file path from the directory: 'assets/sounds/'.
		/// </summary>
		/// <returns>0 if successful, -1 if error.</returns>
		int loadSound(std::string filename);

		/// <summary>
		/// Set name label of the sound.
		/// </summary>
		void setLabel(std::string label);

		/// <summary>
		/// Get name label of the sound.
		/// </summary>
		std::string getLabel() const;

		/// <summary>
		/// Play the sound storied if available and loop if true.
		/// </summary>
		void play(bool loop = false);

		/// <summary>
		/// Stop playing the sound if currently playing.
		/// </summary>
		void stop();

		/// <summary>
		/// Pause the sound if currently playing.
		/// </summary>
		void pause();

		/// <summary>
		/// Get the SFML sound pointer representation of the sound.
		/// </summary>
		sf::Sound* getSound() const;
	};
}