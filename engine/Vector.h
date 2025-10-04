#pragma once

namespace df {

	/// <summary>
	/// CLass to represent a 2d vector with an x and y position
	/// </summary>
	class Vector
	{
	public:
		double x = 0;
		double y = 0;

		/// <summary>
		/// Initilizes vector with and x and y magnitude.
		/// </summary>
		Vector(float x, float y);

		/// <summary>
		/// Computes and returns the magnitude of the vector.
		/// </summary>
		float getMagnitude() const;

		/// <summary>
		/// Normalizes this vector. Throws runtime exception if it's a 0 vector.
		/// </summary>
		void normalize();

		/// <summary>
		/// scales the matrix by the given factor.
		/// </summary>
		void scale(float factor);

		/// <summary>
		/// Operator overload for addition with two vectors.
		/// </summary>
		Vector operator+(const Vector& other) const;

		/// <summary>
		/// Operator overload for addition with a value and a vector.
		/// </summary>
		Vector operator+(const float n) const;
	};
}