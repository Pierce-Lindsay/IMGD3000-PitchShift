#include "Vector.h"
#include <cmath>
#include <stdexcept>

using namespace df;

Vector::Vector(float x, float y) : x(x), y(y) {}

float Vector::getMagnitude() const
{
	return sqrt(x * x + y * y); //pythag
}
void Vector::normalize() //divide elements by magnitude
{
	float magnitude = getMagnitude();
	if (magnitude == 0)
		throw std::runtime_error("Can't normalize a 0 vector.");
	x /= magnitude;
	y /= magnitude;
}

void Vector::scale(float factor)
{
	x *= factor;
	y *= factor;
}

Vector Vector::operator+(const Vector& other) const {
	return Vector(this->x + other.x, this->y + other.y);
}

Vector Vector::operator+(const float n) const {
	return Vector(this->x + n, this->y + n);
}