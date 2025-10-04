#include "Event.h"

using namespace df;

Event::Event()
{}

Event::~Event()
{}

void Event::setType(std::string new_type)
{
	event_type = new_type;
}

std::string Event::getType() const
{
	return event_type;
}