#pragma once
#include <string>
#include "Color.h"
#include"../Vector.h"
namespace df {

	/// <summary>
	/// A frame within a rendered sprite animation.
	/// </summary>
	class Frame
	{
	private:
		int width = 0;
		int height = 0;
		std::string frame_string = ""; //string representation of ascii art frame

	public:
		/// <summary>
		/// Create empty frame
		/// </summary>
		Frame();

		/// <summary>
		/// Create a new frame with the given width, height, and string.
		/// </summary>
		Frame(int width, int height, std::string frame_string);

		/// <summary>
		/// Set the width in characters of the frame to draw.
		/// Does nothing if given width is negative.
		/// </summary>
		void setWidth(int width);

		/// <summary>
		/// Get the width in characters of the frame to draw.
		/// </summary>
		int getWidth() const;

		/// <summary>
		/// Set the height in characters of the frame to draw.
		/// Does nothing if given height is negative.
		/// </summary>
		void setHeight(int height);

		/// <summary>
		/// Get the height in characters of the frame to draw.
		/// </summary>
		int getHeight() const;

		/// <summary>
		/// Set the string of the frame.
		/// </summary>
		void setString(std::string string);

		/// <summary>
		/// Get the string of characters for this frame.
		/// </summary>
		std::string getString() const;

		/// <summary>
		/// Draw this frame centered at the given position of the specified color.
		/// </summary>
		/// <returns>0 if draws successfully, -1 if error in drawing.</returns>
		int draw(Vector position, Color color) const;
	};
}
