#pragma once
#include "../engine/game/object.h"
#include "../engine/graphics/Color.h"

/// <summary>
/// Projectiles that fall where the player can't be and hurt the player.
/// </summary>
class Projectile : public df::Object
{
private:
	df::Color color = df::WHITE;
public:
	const static int Y_SPAWN_POS = 0; //top of screen
	Projectile(float Xpos, df::Color color, float speed, std::string sprite_label);
	int eventHandler(const df::Event* p_event) override;
	int draw() override;
};
