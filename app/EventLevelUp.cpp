#include "EventLevelUp.h"

EventLevelUp::EventLevelUp(int level) : level(level) 
{
	setType(LEVEL_UP_EVENT);
}

void EventLevelUp::setLevel(int level) {
	this->level = level;
}

int EventLevelUp::getLevel() const {
	return level;
}
