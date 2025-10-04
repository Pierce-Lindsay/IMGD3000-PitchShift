#include "SpriteObject.h"
#include "../engine/ResourceManager.h"

SpriteObject::SpriteObject(std::string sprite_label)
{
	setType("SpriteObject::" + sprite_label);
	setSprite(sprite_label);
}

int SpriteObject::eventHandler(const df::Event* p_e)
{
	return 0;
}