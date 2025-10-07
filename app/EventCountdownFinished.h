#pragma once
#include "../engine/Event.h"

const std::string COUNTDOWN_FINISHED_EVENT = "ountdown_finished";

class EventCountdownFinished : public df::Event {
	public:
		EventCountdownFinished();
};
