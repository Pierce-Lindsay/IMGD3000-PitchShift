#pragma once
#include "../engine/game/Object.h"
#include "../engine/game/EventCollision.h"

class Portal : public df::Object {
	private:
		bool to_higher_pitch; // true if portal goes to higher pitch, false if lower pitch

		// Handle collision with player
		void collide(const df::EventCollision* p_collision_event);

		// Handle teleportation event
		void step();

	public:
		Portal();

		void setToHigherPitch(bool to_higher = false);

		bool isToHigherPitch() const;

		int eventHandler(const df::Event* p_e) override;
};