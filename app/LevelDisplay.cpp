#include "LevelDisplay.h"
#include "../engine/graphics/DisplayManager.h"
#include "EventLevelUp.h"
#include "../engine/ResourceManager.h"
#include "../engine/game/EventStep.h"

LevelDisplay::LevelDisplay() {
	setType("LevelDisplay");
	setSolidness(df::Solidness::SPECTRAL);
	setAltitude(4); //high altitude
	setPosition(df::Vector(1, 1)); //top left of screen
}

int LevelDisplay::eventHandler(const df::Event* p_event) {
	if (p_event->getType() == LEVEL_UP_EVENT) {
		const EventLevelUp* p_level_event = dynamic_cast<const EventLevelUp*>(p_event);
		if (p_level_event) {
			level = p_level_event->getLevel();
			//play noise
			RM.getSound("levelUp")->play();
			//flash color
			flashing = true;
			current_color = FLASH_COLOR;
			return 1;
		}
	}
	else if(p_event->getType() == df::STEP_EVENT) {
		const df::EventStep* p_step = dynamic_cast<const df::EventStep*>(p_event);
		if (p_step) {
			if (flashing) {
				flash_time++;
				if (flash_time >= FLASH_DURATION) {
					flashing = false;
					flash_time = 0;
					current_color = DEFAULT_COLOR; //reset color
				}
			}
			return 1;
		}
	}
	return 0; //not handled
}

int LevelDisplay::draw() {
	DM.drawString(getPosition(), "Level: " + std::to_string(level), df::Justification::RIGHT, current_color);
	return 1;
}