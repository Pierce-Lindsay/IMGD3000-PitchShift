#include "OutObject.h"
#include "../engine/LogManager.h"
#include "../engine/game/WorldManager.h"

OutObject::OutObject()
{
	setType("OutObject");
}

int OutObject::eventHandler(const df::Event* p_e)
{
	if (p_e->getType() == df::OUT_EVENT)
	{
		LM.writeLog("OutObject::eventHandler::This object went out of bounds.");
		//delete itself for testing
		WM.markForDelete(this);
		return 1;
	}
	return 0;
}