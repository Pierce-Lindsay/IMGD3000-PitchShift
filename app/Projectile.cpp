#include "Projectile.h"
#include "../engine/LogManager.h"
#include "../engine/game/EventOut.h"
#include "../engine/game/EventCollision.h"
#include "../engine/game/WorldManager.h"
#include "../engine/graphics/DisplayManager.h"
Projectile::Projectile(df::Vector pos, df::Color color, float speed, std::string sprite_label)
{
	setType("Projectile");
	setSolidness(df::Solidness::SPECTRAL);
	setPosition(pos);
	setSpeed(speed);
	setDirection(df::Vector(0, 1)); //down
	setSprite(sprite_label);
	if(getSprite() == NULL) {
		LM.writeLog("Projectile::Projectile: Warning! Sprite not found: %s", sprite_label.c_str());
		return;
	}
	setAltitude(2);
	this->color = color;
}

int Projectile::eventHandler(const df::Event* p_event)
{
	if(p_event->getType() == df::OUT_EVENT) {
		const df::EventOut* p_out_event = dynamic_cast<const df::EventOut*>(p_event);
		LM.writeLog("Projectile::eventHandler: Projectile %d out of bounds below, deleting", getID());
		if (getPosition().y > DM.getVerticalChars() + 5) //went out bottom of screen with some leeway
		WM.markForDelete(this);
		return 1;
	}
	else if(p_event->getType() == df::COLLISION_EVENT) 
	{
		const df::EventCollision* p_collision_event = dynamic_cast<const df::EventCollision*>(p_event);
		LM.writeLog("Projectile::eventHandler: Projectile %d collision", getID());
		WM.markForDelete(this);
		return 1;
	}
	return 0;
}

int Projectile::draw() 
{
	df::Sprite* sp = getSprite(); //projectiles dont have animations, so this is a workaround for colors
	df::Frame f = sp->getFrame(0);
	return f.draw(getPosition(), color);
}

