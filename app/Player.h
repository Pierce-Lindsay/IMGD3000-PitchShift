#pragma once
#include "../engine/game/Object.h"
#include "../engine/input/EventKeyboard.h"

class Player : public df::Object {
	private:
		int health; // player health
		int score; // player score
		float speed; // player speed
		int dx; // horizontal movement direction (-1, 0, 1)

		// Handle user input for movement
		void handleInput(const df::EventKeyboard* p_keyboard_event);

		// Move player based on current direction and speed
		void move();

		// Update player state each game step
		void step();
	public:
		Player();

		~Player();

		int eventHandler(const df::Event* p_e) override;

		// Setters and getters
		void setHealth(int new_health);

		int getHealth() const;

		void setScore(int new_score);

		int getScore() const;
};