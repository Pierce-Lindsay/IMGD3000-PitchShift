#pragma once
#include <string>
#include "Event.h"

namespace df
{
	/// <summary>
	/// A base class for managing in the game engine.
	/// </summary> 
	class Manager
	{
	private:
		std::string type = "undefined";
		bool is_started = false;
		bool is_shutdown = false;

	protected:

		/// <summary>
		/// Set type identifier of this manager
		/// </summary>
		void setType(std::string type);

	public:
		Manager();

		/// <summary>
		/// Destructs dependencies, and automatically calls shutdown if hasn't been shutdown yet.
		/// </summary>
		virtual ~Manager();

		
		/// <summary>
		/// Get type identifier of manager
		/// </summary>
		std::string getType() const;
		
		/// <summary>
		/// Startup manager.
		/// Returns 0 if ok, else negative number.
		virtual int startUp();

		/// <summary>
		/// Shutdown manager
		/// </summary>
		virtual void shutDown();

		/// <summary>
		/// Is the manager started? Has startUp been called successfully.
		/// </summary>
		/// <returns>True if the manager is strated.</returns>
		bool isStarted() const;

		/// <summary>
		/// Sends the given event to all objects in the world.
		/// </summary>
		/// <returns>The amount of objects that handle the event(don't igorne it).</returns>
		int onEvent(const Event* p_event);
	};
}