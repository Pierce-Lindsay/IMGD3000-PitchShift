#include "Sprite.h"
#include "DisplayManager.h"
#include "../LogManager.h"

using namespace df;

Sprite::~Sprite()
{
	frames.clear();
	LM.writeLog("Sprite::~Sprite::Destructed sprite with label: %s", label.c_str());
}

Sprite::Sprite(int max_frames)
{
	max_frames_count = max_frames;
	frames.reserve(max_frames_count); // set vector capacity to max frames count
}

void Sprite::setWidth(int width)
{
	if (width >= 0)
		this->width = width;
}

int Sprite::getWidth() const
{
	return width;
}

void Sprite::setHeight(int height)
{
	if (height >= 0)
		this->height = height;
}

int Sprite::getHeight() const
{
	return height;
}

void Sprite::setColor(Color color)
{
	this->color = color;
}

Color Sprite::getColor() const
{
	return color;
}

int Sprite::getFrameCount() const
{
	return current_frame_count;
}

int Sprite::addFrame(Frame frame)
{
	if (current_frame_count >= max_frames_count)
	{
		LM.writeLog("Sprite::addFrame::Cannot add any more frames to sprite with label: %s, max frame count size for this sprite reached!", label.c_str());
		return -1;
	}
	frames.push_back(frame);
	current_frame_count++;
	return 0;
}

Frame Sprite::getFrame(int frame_number) const
{
	if (frame_number >= current_frame_count || frame_number< 0)
	{
		LM.writeLog("Sprite::getFrame::Cannot get the requested frame: %d, either it exceeds the sprite frame size of: %d, or is negative", frame_number, current_frame_count);
		return Frame();
	}
	return frames[frame_number];
}

void Sprite::setLabel(std::string label)
{
	this->label = label;
}

std::string Sprite::getLabel() const
{
	return label;
}

void Sprite::setSlowdown(int slowdown)
{
	if (slowdown >= 0)
		this->slowdown = slowdown;
}

int Sprite::getSlowdown() const
{
	return slowdown;
}

int Sprite::draw(int frame_number, Vector position) const
{
	return getFrame(frame_number).draw(position, color);
}