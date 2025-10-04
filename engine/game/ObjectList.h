#pragma once
#include "Object.h"

namespace df {

	static const int MAX_OBJECTS = 1000;

	/// <summary>
	/// A class that handles a list(array) of object pointers.
	/// </summary>
	class ObjectList {

	private:
		int count = 0; //current count in the array
		Object* p_obj[MAX_OBJECTS] = {}; //array of object pointers

	public:
		/// <summary>
		/// Create an ObjectList with count 0.
		/// </summary>
		ObjectList();

		/// <summary>
		/// Insert a new Object pointer to the end of the list.
		/// </summary>
		/// <returns>0 if ok, -1 else.</returns>
		int insert(Object* p_o);

		/// <summary>
		/// Remove a Object pointer pointing to the object with the given id. 
		/// Slow if called a bunch of time in sequence. Add a batch remove later?
		/// </summary>
		/// <returns>0 if ok, -1 else.</returns>
		int remove(Object* p_o);

		/// <summary>
		/// Clear the list to 0 elements.
		/// </summary>
		void clear();

		/// <summary>
		/// Return the count of elements in the list.
		/// </summary>
		int getCount() const;

		/// <summary>
		/// Returns whether the list has any elements in it, true if empty, false else.
		/// </summary>
		bool isEmpty() const;

		/// <summary>
		/// Find the given object pointer that points to the object with the same ID in the list.
		/// </summary>
		/// <returns>The position in the list if found, -1 if not. </returns>
		int find(Object* p_o) const;

		/// <summary>
		/// Indexing for list, works like normal array indexing.
		/// </summary>
		Object* &operator[](int index);
	};
}