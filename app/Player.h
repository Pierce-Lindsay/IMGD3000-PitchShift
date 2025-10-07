#pragma once
#include "../engine/game/Object.h"
#include "../engine/input/EventKeyboard.h"
#include "../engine/game/EventCollision.h"
#include "EventTeleport.h"

class Player : public df::Object {
	private:
		int health; // player health
		int score; // player score
		float speed; // player speed
		int dx; // horizontal movement direction (-1, 0, 1)
		int invincibility_timer; // frames of invincibility left
		int invincibility_duration; // duration of invincibility in frames
		bool isHit; // flag to indicate if player was hit
		bool should_teleport; // flag to indicate if player should teleport
		df::Vector teleport_position = df::Vector(0, 0); // position to teleport to

		// Handle user input for movement
		void handleInput(const df::EventKeyboard* p_keyboard_event);

		// Move player based on current direction and speed
		void move();

		// Update player state each game step
		void step();

		// Handle player being hit
		void hit(const df::EventCollision* p_collision_event);

		// Handle teleportation event
		void teleport(const EventTeleport* p_teleport_event);
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