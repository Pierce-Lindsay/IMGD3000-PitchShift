#include "Frame.h"
#include "../LogManager.h"
#include "DisplayManager.h"
#include "../Utility.h"
using namespace df;

Frame::Frame()
{}

Frame::Frame(int width, int height, std::string frame_string) :  width(width), height(height), frame_string(frame_string)
{
}

void Frame::setWidth(int width)
{
	if(width >= 0)
		this->width = width;
}

int Frame::getWidth() const
{
	return width;
}

void Frame::setHeight(int height)
{
	if(height >= 0)
		this->height = height;
}

int Frame::getHeight() const
{
	return height;
}

void Frame::setString(std::string string)
{
	this->frame_string = string;
}

std::string Frame::getString() const
{
	return frame_string;
}

int Frame::draw(Vector position, Color color) const
{
	//dimensions must match string length
	int anticipated_size = frame_string.size();
	int dim_size = width * height;
	if (anticipated_size == 0)
	{
		LM.writeLog("Frame::draw::Failed to draw an empty frame.");
		return -1;
	}
	else if (dim_size != anticipated_size)
	{
		LM.writeLog("Frame::draw::Failed to draw frame, dimensions give size: %d, but actual size is %d.", dim_size, anticipated_size);
		return -1;
	}
	//offsets 1/2 because centered 
	float width_offset = (float)width * 0.5f;
	float height_offset = (float)height * 0.5f;
	//draw each character individually
	int err = 0;
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			Vector temp(position.x + i - width_offset + 0.5, position.y + j - height_offset + 0.5);
			err += DM.drawCh(temp, frame_string[j * width + i], color);
		}
	}
	if (err < 0)
		return -1;
	return 0;
}