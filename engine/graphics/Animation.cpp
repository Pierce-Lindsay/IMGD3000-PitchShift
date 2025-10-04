#include "Animation.h"
#include "../LogManager.h"

using namespace df;

Animation::Animation()
{}

void Animation::setSprite(Sprite* sprite)
{
	this->sprite = sprite;
}

Sprite* Animation::getSprite() const
{
	return sprite;
}

void Animation::setName(std::string name)
{
	this->name = name;
}

std::string Animation::getName() const
{
	return name;
}

void Animation::setIndex(int index)
{
	if(index>= 0)
		current_frame = index;
}

int Animation::getIndex() const
{
	return current_frame;
}

int Animation::getSlowdownCount() const
{
	return slowdown_counter;
}

void Animation::setSlowdownCount(int slowdown)
{
	if (slowdown >= 0)
		slowdown_counter = slowdown;
}

int Animation::draw(Vector position)
{
	int err = 0;
	if (sprite == NULL)
	{
		LM.writeLog("Animation::draw::Cannot draw null sprite.");
		return -1;
	}
	int slowdown = sprite->getSlowdown();
	if (slowdown == 0) //draw at whatever current frame, dont increment
		return sprite->draw(current_frame, position);
	else
	{
		err = sprite->draw(current_frame, position); //draw before so we don't skip 0th frame

		slowdown_counter++;
		if (slowdown_counter >= slowdown)
		{
			slowdown_counter = 0;
			current_frame++;
		}

		if (current_frame >= sprite->getFrameCount()) //after incase of wierd exceptions
			current_frame = 0;

		return err;
	}
}

Box Animation::getBox() const
{
	if (sprite == NULL) //return default box
		return Box(Vector(-0.5, -0.5), 0.99, 0.99); //slightly smaller and offset to top left
	float width = sprite->getWidth();
	float height = sprite->getHeight();
	return Box(Vector(-0.5f * width, -0.5 * height), width * 0.99, height * 0.99); //slightly smaller
}