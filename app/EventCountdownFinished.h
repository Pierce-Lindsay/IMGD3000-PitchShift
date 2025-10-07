#pragma once
#include "../engine/Event.h"

const std::string COUNTDOWN_FINISHED_EVENT = "countdown_finished";

/// <summary>
/// Event for when the countdown finishes.
/// </summary>
class EventCountdownFinished : public df::Event 
{
	public:
		EventCountdownFinished();
};
