#pragma once
#include "../engine/game/Object.h"
#include "../engine/audio/Sound.h"

/// <summary>
/// Class for handling game over of game.
/// </summary>
class GameOver : public df::Object {
	private:
		int time_to_live; //time in frames to live
		df::Sound* p_sound; //pointer to game over sound

		// Update each frame
		void step();
	public:
		//create a new game over object
		GameOver();

		//clean up
		~GameOver();

		int eventHandler(const df::Event* p_e) override;
};