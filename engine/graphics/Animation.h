#pragma once
#include <string>
#include "Sprite.h"
#include "../Box.h"

namespace df {

	/// <summary>
	/// A class taht automatically animates a sprite each time the sprite is drawn.
	/// </summary>
	class Animation
	{
	private:
		Sprite* sprite = NULL; //sprite to be animated
		std::string name = "undefined"; //label for animation
		int current_frame = 0; //handles frame rotation
		int slowdown_counter = 0; //handles slowdown
	public:

		/// <summary>
		/// Create a default animation.
		/// </summary>
		Animation();

		/// <summary>
		/// Set the sprite pointer that the animation uses.
		/// </summary>
		void setSprite(Sprite* sprite);

		/// <summary>
		/// Get the sprite pointer that the animation uses.
		/// </summary>
		Sprite* getSprite() const;

		/// <summary>
		/// Set the name that the animation uses.
		/// </summary>
		void setName(std::string name);

		/// <summary>
		/// Get the name that the animation uses.
		/// </summary>
		std::string getName() const;

		/// <summary>
		/// Set the current frame index of the animation.
		/// Cyclicaly wraps arround.
		/// </summary>
		void setIndex(int index);

		/// <summary>
		/// Gets what the current frame index of teh animation is.
		/// </summary>
		int getIndex() const;

		/// <summary>
		/// Gets what the current slowdoen counter for the animation is.
		/// </summary>
		int getSlowdownCount() const;

		/// <summary>
		/// Sets what the current slowdoen counter for the animation is.
		/// </summary>
		void setSlowdownCount(int slowdown);

		/// <summary>
		/// Draws the animation with the current frame at the position; frame 
		/// decided by the slowdown counter and frame counter and increments
		/// according to the slowdown.
		/// </summary>
		/// <returns>0 if ok, -1 if drawing error.</returns>
		int draw(Vector position);

		/// <summary>
		/// Get the collision box created by the size of the sprite.
		/// </summary>
		Box getBox() const;
	};
}