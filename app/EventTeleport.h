#pragma once
#include "../engine/Event.h"

const std::string TELEPORT_EVENT = "Teleport";

/// <summary>
/// Event for when the player uses a portal to teleport between sides.
/// </summary>
class EventTeleport : public df::Event {
	private:
		bool to_higher_pitch; // true if portal goes to higher pitch, false if lower pitch
	public:
		EventTeleport();

		/// <summary>
		/// Is it a higher pitch transition or lower pitch transition?
		/// </summary>
		/// <param name="to_higher"></param>
		void setToHigherPitch(bool to_higher = false);

		/// <summary>
		/// Get whether it is a higher pitch transition or lower pitch transition.
		/// </summary>
		bool isToHigherPitch() const;
};