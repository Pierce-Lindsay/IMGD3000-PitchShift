#include <chrono>
#pragma once
namespace df {
	/// <summary>
	/// A clock class that starts a time where constructed and can provide splits and start/stops(deltas) in microseconds.
	/// </summary>
	class Clock
	{
	private:
		//previous time the clock cares about
		std::chrono::steady_clock::time_point start;

	public:
		Clock();

		/// <summary>
		/// Gets the time between the last delta call.
		/// </summary>
		/// <returns>Time elapsed since last delta call.</returns>
		long long delta();

		/// <summary>
		/// Gets the time between the last delta call.
		/// </summary>
		/// <returns>Time elapsed since last delta call.</returns>
		long long split() const;
	};
}