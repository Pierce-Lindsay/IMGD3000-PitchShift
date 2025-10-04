#include "EventCollision.h"
using namespace df;

EventCollision::EventCollision() : m_pos(0, 0)
{
	setType(COLLISION_EVENT);
}

EventCollision::EventCollision(Object* obj1, Object* obj2, Vector pos) : obj1(obj1), obj2(obj2), m_pos(pos)
{
	setType(COLLISION_EVENT);
}

void EventCollision::setPos(Vector pos)
{
	m_pos = pos;
}

Vector EventCollision::getPos() const
{
	return m_pos;
}

void EventCollision::setObject1(Object* obj1)
{
	this->obj1 = obj1;
}

Object* EventCollision::getObject1() const
{
	return obj1;
}

void EventCollision::setObject2(Object* obj2)
{
	this->obj2 = obj2;
}

Object* EventCollision::getObject2() const
{
	return obj2;
}