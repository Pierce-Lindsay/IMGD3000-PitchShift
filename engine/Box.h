#pragma once
#include "Vector.h"

namespace df {
	/// <summary>
	/// A 2d box with a top-left corner position, width, and height.
	/// </summary>
	class Box {
	private:
		Vector corner; //upper left corner of box
		float width = 0; //horizontal width
		float height = 0; //verticla height
	public:
		/// <summary>
		/// create box with top left corner at 0, 0 with 0 width and 0 height in char spaces.
		/// </summary>
		Box();

		/// <summary>
		/// Create box with top-left-corner pos and the given width and height in char spaces.
		/// </summary>
		Box(Vector corner_pos, float width, float height);

		/// <summary>
		/// Set the position of the box's top left corner in char spaces.
		/// </summary>
		void setCorner(Vector pos);

		/// <summary>
		/// Get the position of the box's top left corner in char spaces.
		/// </summary>
		Vector getCorner() const;

		/// <summary>
		/// Set the horizontal width of the box in char spaces.
		/// </summary>
		void setHorizontal(float width);

		/// <summary>
		/// Get the horizontal width of the box in char spaces.
		/// </summary>
		float getHorizontal() const;

		/// <summary>
		/// Set the vertical height of the box in char spaces.
		/// </summary>
		void setVertical(float height);

		/// <summary>
		/// Get the vertical height of the box in char spaces.
		/// </summary>
		float getVertical() const;
	};
}