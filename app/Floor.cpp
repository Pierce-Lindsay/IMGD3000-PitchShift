#include "Floor.h"
#include "../engine/LogManager.h"

#include "../engine/game/WorldManager.h"
#include "../engine/graphics/Animation.h"
#include "../engine/graphics/Sprite.h"

Floor::Floor() {
	setType("Floor");
	setSolidness(df::Solidness::SPECTRAL);
	setSprite("floor");
	if(getSprite() == NULL) {
		LM.writeLog("Floor::Floor: Warning! Sprite not found: floor");
		return;
	}
	setAltitude(0);
	setSpeed(0);
}

Floor::~Floor() {
}

int Floor::eventHandler(const df::Event* p_e) {
	if (p_e->getType() == TELEPORT_EVENT) {
		const EventTeleport* p_teleport_event = dynamic_cast<const EventTeleport*>(p_e);
		changeColor(p_teleport_event);
		return 1;
	}
	return 0;
}

void Floor::changeColor(const EventTeleport* p_teleport_event) {
	df::Sprite* p_sprite = getSprite();
	if (p_sprite == NULL) {
		LM.writeLog("Floor::changeColor: Warning! Sprite not found: floor");
		return;
	}

	df::Color red = df::RED;
	df::Color green = df::GREEN;
	df::Color blue = df::BLUE;

	if (p_teleport_event->isToHigherPitch()) {
		if(isSameColor(p_sprite->getColor(), red)) {
			LM.writeLog("Floor::changeColor: Changing floor color from RED to GREEN");
			p_sprite->setColor(green);
			return;
		}
		if(isSameColor(p_sprite->getColor(), green)) {
			LM.writeLog("Floor::changeColor: Changing floor color from GREEN to BLUE");
			p_sprite->setColor(blue);
			return;
		}
		if (isSameColor(p_sprite->getColor(), blue)) {
			LM.writeLog("Floor::changeColor: BLUE is the highest pitch color, so no change.");
			p_sprite->setColor(blue);
			return;
		}
	}
	else {
		if (isSameColor(p_sprite->getColor(), blue)) {
			LM.writeLog("Floor::changeColor: Changing floor color from BLUE to GREEN");
			p_sprite->setColor(green);
			return;
		}
		if (isSameColor(p_sprite->getColor(), green)) {
			LM.writeLog("Floor::changeColor: Changing floor color from GREEN to RED");
			p_sprite->setColor(red);
			return;
		}
		if (isSameColor(p_sprite->getColor(), red)) {
			LM.writeLog("Floor::changeColor: RED is the lowest pitch color, so no change.");
			p_sprite->setColor(red);
			return;
		}
	}

}

bool Floor::isSameColor(df::Color c1, df::Color c2) {
	return (c1.getR() == c2.getR() && c1.getG() == c2.getG() && c1.getB() == c2.getB());
}