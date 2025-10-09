#include "Title.h"

#include "../engine/LogManager.h"
#include "../engine/graphics/DisplayManager.h"
#include "../engine/game/EventStep.h"
#include "../engine/graphics/Sprite.h"

Title::Title() {
	setType("Title");
	setSolidness(df::Solidness::SPECTRAL);
	setPosition(df::Vector((float)(DM.getHorizontalChars() / 2), 5.0f));
	setSprite("title");
	setAltitude(df::MAX_ALTITUDE);
}

int Title::eventHandler(const df::Event* p_e) {
	if(p_e->getType() == df::STEP_EVENT) {
		const df::EventStep* p_step = dynamic_cast<const df::EventStep*>(p_e);
		//change color of title suring animation
		df::Sprite* p_sprite = getSprite();
		df::Color colors[] = { df::RED, df::ORANGE, df::YELLOW, df::GREEN, df::BLUE, df::PURPLE, df::WHITE,
		df::TURQUOISE, df::GRAY};

		if (p_step->getStepCount() % 10 == 0) {
			int random_index = rand() % (sizeof(colors) / sizeof(colors[0]));
			p_sprite->setColor(colors[random_index]);
		}
		return 1;
	}
	return 0;
}