#pragma once
#include "../engine/Event.h"

const std::string CHANGE_COLOR_EVENT = "change_color";

/// <summary>
/// Event for changing the floor.
/// </summary>
class EventChangeColor : public df::Event {
	private:
		bool to_higher_pitch; // true if portal goes to higher pitch, false if lower pitch
	public:
		EventChangeColor();

		void setToHigherPitch(bool to_higher = false);

		bool isToHigherPitch() const;
};