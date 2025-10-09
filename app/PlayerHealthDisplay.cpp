#include "PlayerHealthDisplay.h"

PlayerHealthDisplay::PlayerHealthDisplay()
{
	setType("player-health-display");
	setAltitude(df::MAX_ALTITUDE);
	setSolidness(df::Solidness::SPECTRAL);
}

void PlayerHealthDisplay::setHealth(int health)
{
	this->health = health;
}

int PlayerHealthDisplay::draw()
{
	std::string display = "Health: " + std::to_string(health);
	return DM.drawString(draw_pos, display, df::Justification::LEFT, color);
}