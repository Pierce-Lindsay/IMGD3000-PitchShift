#pragma once
#include "../engine/game/object.h"
#include "../engine/graphics/DisplayManager.h"

/// <summary>
/// Display for the player's current hp left.
/// </summary>
class PlayerHealthDisplay : public df::Object
{
public:
	PlayerHealthDisplay();

	/// <summary>
	/// Set the health of player.
	/// </summary>
	void setHealth(int health);

	/// <summary>
	/// Draw the hp of the player at the top right.
	/// </summary>
	int draw() override;

private:
	int health = 0; // health of player
	const df::Vector draw_pos = df::Vector(DM.getHorizontalChars() - 1, 2); //draw pos
	const df::Color color = df::GREEN;
};
