#include "Countdown.h"
#include "../engine/graphics/DisplayManager.h"

Countdown::Countdown() {
	setType("Countdown");
	setSolidness(df::Solidness::SPECTRAL);
	setAltitude(3);
	setPosition(df::Vector((float)(DM.getHorizontalChars() / 2), (float)(DM.getVerticalChars() / 2)));
}

void Countdown::start() {
	countdownClock.delta(); //reset clock
	started = true;
}

int Countdown::draw() {
	if (!started) 
		return 0;

	int seconds = initial_time - countdownClock.split() / 1000000.0f;
	if (seconds < 0)
		return 0;
	std::string to_draw = std::to_string(seconds + 1); //add one so it shows 3, 2, 1, GO!
	return DM.drawCh(getPosition(), to_draw[0], df::YELLOW);
}

bool Countdown::isFinished() const {
	return countdownClock.split() / 1000.0f > initial_time / 1000.0f;
}
