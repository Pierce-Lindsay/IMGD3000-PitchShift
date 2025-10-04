#include "TestDrawingObject.h"
#include "../engine/graphics/DisplayManager.h"
#include "../engine/LogManager.h"
#include "../engine/game/WorldManager.h"
#include "../engine/ResourceManager.h"
#include "../engine/game/EventOut.h"

TestDrawingObject::TestDrawingObject(std::string whatToDraw)
{
	setType("TestDrawingObject");
	this->whatToDraw = whatToDraw;
	setSolidness(df::Solidness::SPECTRAL);
}
int TestDrawingObject::eventHandler(const df::Event* p_e)
{
	if (p_e->getType() == df::OUT_EVENT)
	{
		RM.getSound("explode")->play();
		LM.writeLog("TestDrawingObject::Leaving the world, out event triggered");
		WM.markForDelete(this);
	}
	return 0;
}

int TestDrawingObject::draw()
{
	int err = 0;
	if(whatToDraw.size() == 1)
		err = DM.drawCh(getPosition(), whatToDraw[0], color);
	else
		err = DM.drawString(getPosition(), whatToDraw, just, color);
	if (err == -1)
		LM.writeLog("TestDrawingObject::draw::Failed to draw.");
	return err;
}


void TestDrawingObject::setColor(df::Color c)
{
	color = c;
}

void TestDrawingObject::setJust(df::Justification j)
{
	just = j;
}