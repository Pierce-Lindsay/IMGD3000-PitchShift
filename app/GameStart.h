#pragma once
#include "../engine/audio/Music.h"
#include "../engine/game/Object.h"

class GameStart : public df::Object {

private:
	df::Music* p_music; //pointer to start music

	// Start the game
	void start();

public:
	GameStart();
	int eventHandler(const df::Event* p_e) override;
	void playMusic();
};
