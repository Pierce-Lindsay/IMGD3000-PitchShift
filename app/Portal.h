#pragma once
#include "../engine/game/Object.h"
#include "../engine/game/EventCollision.h"

/// <summary>
/// Class for handling portals that teleport the player between higher and lower pitch sides.
/// </summary>
class Portal : public df::Object {
	private:
		bool to_higher_pitch; // true if portal goes to higher pitch, false if lower pitch

		// Handle collision with player
		void collide(const df::EventCollision* p_collision_event);

		// Handle teleportation event
		void step();

	public:
		Portal();

		/// <summary>
		/// Set event to be a higher pitch transition?.
		/// </summary>
		void setToHigherPitch(bool to_higher = false);

		/// <summary>
		/// Is event a higher pitch transition.
		/// </summary>
		bool isToHigherPitch() const;

		int eventHandler(const df::Event* p_e) override;
};