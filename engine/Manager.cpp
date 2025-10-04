#include "Manager.h"
#include "game/WorldManager.h"

using namespace df;

Manager::Manager() {}

Manager::~Manager() 
{
	//if we havn't been shutdown, do it now
	if (!is_shutdown)
		shutDown();
}

void Manager::setType(std::string type) 
{
	this->type = type;
}

std::string Manager::getType() const
{
	return type;
}

int Manager::startUp()
{
	//default startup succeeds every time
	is_started = true;
	return 0;
}

void Manager::shutDown()
{
	//default shutdown
	is_shutdown = true;
	is_started = false;
}

bool Manager::isStarted() const
{
	return is_started;
}

int Manager::onEvent(const Event* p_event)
{
	int count = 0;
	auto objects = WM.getAllObjects();
	for (int i = 0; i < objects.getCount(); i++)
	{
		if (objects[i]->eventHandler(p_event))
			count++;
	}
	return count;
}