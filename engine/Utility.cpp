#include "Utility.h"
#include "graphics/DisplayManager.h"

float df::charHeight()
{
	return DM.getVerticalPixels() / (float)DM.getVerticalChars();
}

float df::charWidth()
{
	return DM.getHorizontalPixels() / (float)DM.getHorizontalChars();
}

df::Vector df::spacesToPixels(df::Vector spaces)
{
	spaces.x = df::charWidth() * spaces.x;
	spaces.y = df::charHeight() * spaces.y;
	return spaces;
}

df::Vector df::pixelsToSpaces(df::Vector pixels)
{
	pixels.x = pixels.x / df::charWidth();
	pixels.y = pixels.y / df::charHeight();
	return pixels;
}

bool df::positionsIntersect(df::Vector p1, df::Vector p2)
{
	return abs(p1.x - p2.x) <= 1 && abs(p1.y - p2.y) <= 1;
}

bool df::boxIntersectsBox(df::Box b1, df::Box b2)
{
	float b1x1 = b1.getCorner().x;
	float b1x2 = b1x1 + b1.getHorizontal();
	float b1y1 = b1.getCorner().y;
	float b1y2 = b1y1 + b1.getVertical();

	float b2x1 = b2.getCorner().x;
	float b2x2 = b2x1 + b2.getHorizontal();
	float b2y1 = b2.getCorner().y;
	float b2y2 = b2y1 + b2.getVertical();

	bool x_overlap = b2x1 <= b1x1 && b1x1 <= b2x2 || //x-axis overlap?
		b1x1 <= b2x1 && b2x1 <= b1x2;

	bool y_overlap = b2y1 <= b1y1 && b1y1 <= b2y2 || //y-axis overlap?
		b1y1 <= b2y1 && b2y1 <= b1y2;

	return x_overlap && y_overlap; //need overlaps in box dimensions
}


df::Box df::getWorldBox(const df::Object* obj)
{
	Vector corner = obj->getBox().getCorner();
	Vector obj_pos = obj->getPosition();
	corner = corner + obj_pos;
	return Box(corner, obj->getBox().getHorizontal(), obj->getBox().getVertical());
}

df::Box df::getWorldBox(const df::Object* obj, df::Vector where)
{
	Vector corner = obj->getBox().getCorner();
	corner = corner + where;
	return Box(corner, obj->getBox().getHorizontal(), obj->getBox().getVertical());
}