#pragma once
#include "../engine/Event.h"

const std::string GAME_END_EVENT = "game_end";
class EventGameEnd : public df::Event
{
public:
	EventGameEnd(); //just exists to notify things when game is ending(update score and such)
};