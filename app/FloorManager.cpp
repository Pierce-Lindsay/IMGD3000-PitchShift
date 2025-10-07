#include "FloorManager.h"
#include "../engine/ResourceManager.h"
#include "../engine/LogManager.h"

FloorManager::FloorManager(std::string floor_label) : floor_label(floor_label)
{
	setType("FloorManager");
	setSolidness(df::Solidness::SPECTRAL);
}

int FloorManager::eventHandler(const df::Event* p_e) 
{
	if (p_e->getType() == CHANGE_COLOR_EVENT) {
		const EventChangeColor* p_color_event = dynamic_cast<const EventChangeColor*>(p_e);
		if (p_color_event) {
			changeColor(p_color_event);
		}
	}
	return 0;
}

void FloorManager::changeColor(const EventChangeColor* p_color_event) {
	df::Sprite* p_sprite = RM.getSprite(floor_label);
	if (p_sprite == NULL) {
		LM.writeLog("FloorManager::changeColor: Warning! Sprite not found: floor");
		return;
	}

	df::Color red = df::RED;
	df::Color green = df::GREEN;
	df::Color blue = df::BLUE;

	if (p_color_event->isToHigherPitch()) {
		if (isSameColor(p_sprite->getColor(), red)) {
			p_sprite->setColor(green);
			return;
		}
		if (isSameColor(p_sprite->getColor(), green)) {
			p_sprite->setColor(blue);
			return;
		}
		if (isSameColor(p_sprite->getColor(), blue)) {
			p_sprite->setColor(blue);
			return;
		}
	}
	else {
		if (isSameColor(p_sprite->getColor(), blue)) {
			p_sprite->setColor(green);
			return;
		}
		if (isSameColor(p_sprite->getColor(), green)) {
			p_sprite->setColor(red);
			return;
		}
		if (isSameColor(p_sprite->getColor(), red)) {
			p_sprite->setColor(red);
			return;
		}
	}

}

bool FloorManager::isSameColor(const df::Color& c1, const df::Color& c2) {
	return (c1.getR() == c2.getR() && c1.getG() == c2.getG() && c1.getB() == c2.getB());
}