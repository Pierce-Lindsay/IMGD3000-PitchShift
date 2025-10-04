#include "Box.h"

using namespace df;

Box::Box(): corner(0, 0)
{}

Box::Box(Vector corner_pos, float width, float height): corner(corner_pos), width(width), height(height)
{}

void Box::setCorner(Vector pos)
{
	corner = pos;
}

Vector Box::getCorner() const
{
	return corner;
}

void Box::setHorizontal(float width)
{
	this->width = width;
}

float Box::getHorizontal() const
{
	return width;
}

void Box::setVertical(float height)
{
	this->height = height;
}

float Box::getVertical() const
{
	return height;
}