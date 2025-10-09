#pragma once
#include "../engine/game/object.h"
#include "../engine/graphics/DisplayManager.h"

class PlayerHealthDisplay : public df::Object
{
public:
	PlayerHealthDisplay();

	void setHealth(int health);

	int draw() override;

private:
	int health = 0;
	const df::Vector draw_pos = df::Vector(DM.getHorizontalChars() - 1, 2);
	const df::Color color = df::GREEN;
};
