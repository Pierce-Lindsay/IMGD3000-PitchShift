#pragma once
#include "Frame.h"
#include <string>
#include <vector>

namespace df {
	class Sprite {

	private:
		int width = 0; //width of sprite
		int height = 0; //height of sprite
		int max_frames_count = 0; //max frame in sprite
		int current_frame_count = 0; //current size of frames
		Color color = WHITE; //color of sprite
		int slowdown = 1; // slowdown of animation(0 is don't animate, 1 is no slowdown)
		std::vector<Frame> frames; //automatically dynamically allocates and handles frames
		std::string label = "undefined"; //label of sprite
		Sprite(); // private to disallow use

	public:

		~Sprite();

		Sprite(int max_frames);

		/// <summary>
		/// Set the width in characters of the sprite to draw.
		/// </summary>
		void setWidth(int width);

		/// <summary>
		/// Get the width in characters of the sprite to draw.
		/// </summary>
		int getWidth() const;

		/// <summary>
		/// Set the height in characters of the sprite to draw.
		/// </summary>
		void setHeight(int height);

		/// <summary>
		/// Get the height in characters of the sprite to draw.
		/// </summary>
		int getHeight() const;

		/// <summary>
		/// Set the color of the sprite to draw.
		/// </summary>
		void setColor(Color color);

		/// <summary>
		/// Get the color of the sprite to draw.
		/// </summary>
		Color getColor() const;

		/// <summary>
		/// Get the current count of frames in the sprite animation.
		/// </summary>
		int getFrameCount() const;

		/// <summary>
		/// Add a frame to the list of frames in the animation.
		/// </summary>
		/// <returns>0 if frame added successfully, -1 if added frame would exceed max size.</returns>
		int addFrame(Frame frame);

		/// <summary>
		/// Get the frame with the given index.
		/// </summary>
		Frame getFrame(int frame_number) const;

		/// <summary>
		/// Set the string label of the sprite.
		/// </summary>
		void setLabel(std::string label);

		/// <summary>
		/// Get the string label of the sprite.
		/// </summary>
		std::string getLabel() const;

		/// <summary>
		/// Set the slowdown of the sprite, 0 is no animation, 1 is no slowdown.
		/// </summary>
		void setSlowdown(int slowdown);

		/// <summary>
		/// Get the slowdown of the sprite, 0 is no animation, 1 is no slowdown.
		/// </summary>
		int getSlowdown() const;

		/// <summary>
		/// Draw the sprite centered at the given position on the given frame.
		/// </summary>
		/// <returns>0 if successful, -1 if failed to draw.</returns>
		int draw(int frame_number, Vector position) const;	
	};
}