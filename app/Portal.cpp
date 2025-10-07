#include "Portal.h"

#include "../engine/LogManager.h"
#include "../engine/game/WorldManager.h"
#include "EventTeleport.h"
#include "../engine/game/EventStep.h"

Portal::Portal() {
	setType("Portal");
	to_higher_pitch = true;
	setAltitude(1);
	setSolidness(df::Solidness::SOFT);
	if (getSprite() == NULL) {
		LM.writeLog("Portal::Portal: Warning! Sprite not found: portal");
		return;
	}
	setSpeed(0);
}

void Portal::setToHigherPitch(bool to_higher) {
	to_higher_pitch = to_higher;
}

bool Portal::isToHigherPitch() const {
	return to_higher_pitch;
}

void Portal::collide(const df::EventCollision* p_collision_event) {
	EventTeleport teleport_event;

	teleport_event.setToHigherPitch(to_higher_pitch);

	if (p_collision_event->getObject1()->getType() == "Player" ||
		p_collision_event->getObject2()->getType() == "Player") {

		LM.writeLog("Portal::collide: Player collided with portal, transitioning pitch.");
		WM.onEvent(&teleport_event);
	}
}

int Portal::eventHandler(const df::Event* p_e) {
	if (p_e->getType() == df::COLLISION_EVENT) {
		const df::EventCollision* p_collision_event = dynamic_cast<const df::EventCollision*>(p_e);
		collide(p_collision_event);
		return 1;
	}
	if (p_e->getType() == df::STEP_EVENT) {
		step();
		return 1;
	}
	return 0;
}

void Portal::step() {}