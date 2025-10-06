#include "EventTeleport.h"

EventTeleport::EventTeleport() {
	setType(TELEPORT_EVENT);
	to_higher_pitch = true;
}

void EventTeleport::setToHigherPitch(bool to_higher) {
	to_higher_pitch = to_higher;
}

bool EventTeleport::isToHigherPitch() const {
	return to_higher_pitch;
}