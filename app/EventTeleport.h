#pragma once
#include "../engine/Event.h"

const std::string TELEPORT_EVENT = "Teleport";

class EventTeleport : public df::Event {
	private:
		bool to_higher_pitch; // true if portal goes to higher pitch, false if lower pitch
	public:
		EventTeleport();

		void setToHigherPitch(bool to_higher = false);

		bool isToHigherPitch() const;
};