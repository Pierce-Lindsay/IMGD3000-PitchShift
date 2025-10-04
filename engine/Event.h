#pragma once
#include <string>

namespace df {
	/// <summary>
	/// A base class for events to inherit from in the engine.
	/// </summary>
	class Event {

	private:
		std::string event_type = "undefined"; //subclass type (user-defined)

	public:

		/// <summary>
		/// Create event with default settings.
		/// </summary>
		Event();

		/// <summary>
		/// Destructor for an event.
		/// </summary>
		virtual ~Event();

		/// <summary>
		/// Set the subclass type of the event.
		/// </summary>
		void setType(std::string new_type);

		/// <summary>
		/// Get the subclass type of the event.
		/// </summary>
		std::string getType() const;
	};
}