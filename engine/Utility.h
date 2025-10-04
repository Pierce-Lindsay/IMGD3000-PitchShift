#pragma once
#include "Vector.h"
#include "Box.h"
#include "game/Object.h"
namespace df {

	/// <summary>
	/// Returns the height of a display ascii character based on window sizes.
	/// </summary>
	float charHeight();

	/// <summary>
	/// Returns the width of a display ascii character based on window sizes.
	/// </summary>
	float charWidth();

	/// <summary>
	/// Converts vector coordinates in ascii character spaces to pixels.
	/// </summary>
	Vector spacesToPixels(Vector spaces);

	/// <summary>
	/// Converts vector coordinates in pixels to ascii character spaces.
	/// </summary>
	Vector pixelsToSpaces(Vector pixels);

	/// <summary>
	/// Determine whether the two vectors are within 1 "unit" "preferably space" of eachother.
	/// </summary>
	bool positionsIntersect(Vector p1, Vector p2);

	/// <summary>
	/// Determine whether the two boxes overlap eachother.
	/// </summary>
	bool boxIntersectsBox(df::Box b1, df::Box b2);

	/// <summary>
	/// Get the objects collision box at its world position.
	/// </summary>
	Box getWorldBox(const Object* obj);

	/// <summary>
	/// Get the objects collision box at its world position if moved to where.
	/// </summary>
	Box getWorldBox(const Object* obj, Vector where);
}