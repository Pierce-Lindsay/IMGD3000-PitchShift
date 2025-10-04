#include "Object.h"
#include "WorldManager.h"
#include "../graphics/DisplayManager.h"
#include "../LogManager.h"
#include "../ResourceManager.h"
using namespace df;

int next_id{ 0 }; //the id to apply to the next constructed object

Object::Object() :pos(0, 0), v_direction(0, 0), altitude(MAX_ALTITUDE/2), collision_box(Vector(-0.5, -0.5), 0.99, 0.99) //collision box slightly smaller
{
	////setup unique id
	id = next_id;
	next_id++;
	WM.insertObject(this); //add object to world
}

Object::~Object()
{
	//already being deleted, but make sure we arn't in WM anymore
	WM.removeObject(this);
}

void Object::setID(int new_id)
{
	id = new_id;
}

int Object::getID() const
{
	return id;
}

void Object::setType(std::string new_type)
{
	type = new_type;
}

std::string Object::getType() const
{
	return type;
}

void Object::setPosition(Vector new_pos)
{
	pos = new_pos;
}

void Object::setVelocity(Vector new_velocity)
{
	if (new_velocity.x == 0 && new_velocity.y == 0)
	{
		speed = 0;
		v_direction = new_velocity;
	}
	else
	{
		speed = new_velocity.getMagnitude();
		new_velocity.normalize();
		v_direction = new_velocity;
	}
}

Vector Object::getVelocity() const
{
	return Vector(v_direction.x * speed, v_direction.y * speed);
}

Vector Object::getPosition() const
{
	return pos;
}

void Object::setMarkForDelete(bool b)
{
	marked_for_delete = b;
}

bool Object::getMarkForDelete() const
{
	return marked_for_delete;
}

int Object::eventHandler(const Event* p_e)
{
	//ignore and return
	return 0;
}

int Object::draw()
{
	return animation.draw(pos);
}

 int Object::getAltitude() const
{
	return altitude;
}

int Object::setAltitude(int new_altitude)
{
	if (new_altitude < MIN_ALTITUDE || new_altitude>MAX_ALTITUDE)
	{
		LM.writeLog("Object::setAltitude::Failed to set altitude of %d, to object with id: %d, as it was out of the required altitude range.", new_altitude, id);
		return -1;
	}
	altitude = new_altitude;
	return 0;
}


float Object::getSpeed() const
{
	return speed;
}


void Object::setDirection(Vector unit_vector)
{
	float mag = unit_vector.getMagnitude();

	if (mag != 1 && mag != 0) //normalize just in case
		unit_vector.normalize();

	v_direction = unit_vector;
}


Vector Object::getDirection() const
{
	return v_direction;
}


Vector Object::predictPosition() const
{
	Vector v = v_direction;
	v.scale(speed);
	return pos + v;
}

void Object::setSpeed(float new_speed)
{
	speed = new_speed;
}

void Object::setSolidness(Solidness solid)
{
	solidness = solid;
}

Solidness Object::getSolidness() const
{
	return solidness;
}

bool Object::isSolid() const
{
	return solidness != Solidness::SPECTRAL;
}

Sprite* Object::getSprite() const
{
	return animation.getSprite();
}

int Object::setSprite(std::string sprite_label)
{
	auto sprite = RM.getSprite(sprite_label);
	if (sprite == NULL)
	{
		LM.writeLog("Object::setSprite::Faoled to set sprite with label: %s, sprite not findable with ResourceManager.", sprite_label.c_str());
		return -1;
	}

	animation.setSprite(sprite);
	animation.setName(sprite_label);
	collision_box = animation.getBox();
	return 0;
}

Box Object::getBox() const
{
	return collision_box;
}

void Object::setBox(Box box)
{
	collision_box = box;
}