#include "Countdown.h"
#include "../engine/graphics/DisplayManager.h"
#include "EventCountdownFinished.h"
#include "../engine/game/WorldManager.h"

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
	if (!started || finished) 
		return 0;

	int seconds = (initial_time - countdownClock.split() / 1000.0f)/1000.f;
	if (seconds < 0)
	{
		enableFinished();
		return 0;
	}
	std::string to_draw = std::to_string(seconds); //add one so it shows 3, 2, 1, GO!
	return DM.drawCh(getPosition(), to_draw[0], df::YELLOW);
}

bool Countdown::isFinished() const {
	return finished;
}

void Countdown::enableFinished()
{
	finished = true;
	df::Event* p_event = new EventCountdownFinished();
	WM.onEvent(p_event);
}
