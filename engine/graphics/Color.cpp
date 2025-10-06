#include "Color.h"
#include <algorithm>

using namespace df;

const Color df::WHITE(255, 255, 255, 255);
const Color df::RED(255, 0, 0, 255);
const Color df::BLUE(0, 0, 255, 255);
const Color df::GREEN(0, 255, 0, 255);
const Color df::TURQUOISE(0, 255, 255, 255);
const Color df::GRAY(50, 50, 50, 255);
const Color df::PURPLE(255, 0, 255, 255);
const Color df::YELLOW(255, 255, 0, 255);
const Color df::ORANGE(255, 140, 0, 255);
const Color df::BLACK;

Color::Color(sf::Color sfml_color)
{
	r = sfml_color.r;
	g = sfml_color.g;
	b = sfml_color.b;
	a = sfml_color.a;
	sfml_color = sf::Color(r, g, b, a);
}

Color::Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a) : r(r), g(g), b(b), a(a)
{
	sfml_color = sf::Color(r, g, b, a);
}

sf::Color Color::getSFMLColor()
{
	if(color_changed)
	{
		sfml_color = sf::Color(r, g, b, a);
		color_changed = false;
	}
	return sfml_color;
}
uint8_t Color::getR() const
{
	return r;
}
uint8_t Color::getG() const
{
	return g;
}
uint8_t Color::getB() const
{
	return b;
}
uint8_t Color::getA() const
{
	return a;
}
void Color::setR(uint8_t r)
{
	this->r = r;
	color_changed = true;
}
void Color::setG(uint8_t g)
{
	this->g = g;
	color_changed = true;
}
void Color::setB(uint8_t b)
{
	this->b = b;
	color_changed = true;
}
void Color::setA(uint8_t a)
{
	this->a = a;
	color_changed = true;
}

df::Color Color::colorFromString(std::string str_color)
{
	std::transform(str_color.begin(), str_color.end(), str_color.begin(), ::tolower);
	if (str_color == "red")
		return RED;
	else if (str_color == "green")
		return GREEN;
	else if (str_color == "purple")
		return PURPLE;
	else if (str_color == "blue")
		return BLUE;
	else if (str_color == "black")
		return BLACK;
	else if (str_color == "yellow")
		return YELLOW;
	else if (str_color == "orange")
		return ORANGE;
	else if (str_color == "gray")
		return GRAY;
	else if (str_color == "turquoise")
		return TURQUOISE;
	else
		return WHITE;
}