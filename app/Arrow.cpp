#include "Arrow.h"
#include "../engine/game/EventOut.h"
#include "../engine/ResourceManager.h"
#include "../engine/game/WorldManager.h"

Arrow::Arrow(bool right, df::Vector pos)
{
	setType("arrow");
	setSolidness(df::Solidness::SPECTRAL);
	setAltitude(1);
	setPosition(pos);
	if (right)
	{
		setSprite("right-arrow");
		setVelocity(df::Vector(3, 0));
	}
	else
	{
		setSprite("left-arrow");
		setVelocity(df::Vector(-3, 0));
	}
}


int Arrow::eventHandler(const df::Event* p_e)
{
	if (p_e->getType() == df::OUT_EVENT)
	{
		WM.markForDelete(this); //clean up on oob
		return 1;
	}
	return 0;
}