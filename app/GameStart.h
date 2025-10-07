#pragma once
#include "../engine/audio/Music.h"
#include "../engine/game/Object.h"


/// <summary>
/// Class for inititializing the game when the player presses 'P' to play.
/// </summary>
class GameStart : public df::Object {

private:
	df::Music* p_music; //pointer to start music

	// Start the game
	void start();

public:
	GameStart();

	int eventHandler(const df::Event* p_e) override;

	/// <summary>
	/// play the start music
	/// </summary>
	void playMusic();
};
