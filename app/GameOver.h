#pragma once
#include "../engine/game/Object.h"
#include "../engine/audio/Sound.h"

class GameOver : public df::Object {
	private:
		int time_to_live; //time in frames to live
		df::Sound* p_sound; //pointer to game over sound

		// Update each frame
		void step();
	public:
		GameOver();
		~GameOver();
		int eventHandler(const df::Event* p_e) override;

};