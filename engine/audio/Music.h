#pragma once
#include <string>
#include "SFML/Audio.hpp"

namespace df {

	const std::string MUSIC_FILE_DIRECTORY = "assets/music/";
	/// <summary>
	/// Class for handling Musics and playing them.
	/// </summary>
	class Music
	{
	private:
		sf::Music music; //sfml Music 
		std::string label = "undefined"; //name of the Music
		Music(Music const&);
		void operator=(Music const&);
		bool valid = false; //set to true when music file is actually opened

	public:
		/// <summary>
		/// Create default Music (no data).
		/// </summary>
		Music();

		/// <summary>
		/// Destruct Music and handle dependencies.
		/// </summary>
		~Music();

		/// <summary>
		/// Load the Music with the given file path from the directory: 'assets/music/'.
		/// </summary>
		/// <returns>0 if successful, -1 if error.</returns>
		int loadMusic(std::string filename);

		/// <summary>
		/// Set name label of the Music.
		/// </summary>
		void setLabel(std::string label);

		/// <summary>
		/// Get name label of the Music.
		/// </summary>
		std::string getLabel() const;

		/// <summary>
		/// Play the Music storied if available and loop if true.
		/// </summary>
		void play(bool loop = false);

		/// <summary>
		/// Stop playing the Music if currently playing.
		/// </summary>
		void stop();

		/// <summary>
		/// Pause the Music if currently playing.
		/// </summary>
		void pause();

		/// <summary>
		/// Get the pointer to the SFML Music representation of the Music.
		/// </summary>
		sf::Music* getMusic();
	};
}