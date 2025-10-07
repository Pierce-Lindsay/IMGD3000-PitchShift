#include "EventChangeColor.h"

EventChangeColor::EventChangeColor() {
	setType(CHANGE_COLOR_EVENT);
	to_higher_pitch = true;
}

void EventChangeColor::setToHigherPitch(bool to_higher) {
	to_higher_pitch = to_higher;
}

bool EventChangeColor::isToHigherPitch() const {
	return to_higher_pitch;
}