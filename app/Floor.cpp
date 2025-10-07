#include "Floor.h"
#include "../engine/LogManager.h"

#include "../engine/game/WorldManager.h"
#include "../engine/graphics/Animation.h"
#include "../engine/graphics/Sprite.h"
#include "../engine/game/EventStep.h"

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