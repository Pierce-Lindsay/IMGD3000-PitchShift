#pragma once
#include "../engine/game/object.h"
#include "../engine/Clock.h"

/// <summary>
/// Countdown timer to be displayed at start of game, changes dispay of character depending on time left.
/// </summary>
class Countdown : public df::Object {
	public:
		Countdown();
		/// <summary>
		/// Inits the countdown.
		/// </summary>
		void start();

		/// <summary>
		/// Boolean indicating whether the countdown has finished.
		/// </summary>
		/// <returns></returns>
		bool isFinished() const;
	private:
		int draw() override;
		float initial_time = 5000; //initial time in milliseconds
		df::Clock countdownClock;
		bool started = false;
		bool finished = false;

		/// <summary>
		/// Set to the finished state, meaning it won't draw anything. Send finished event.
		/// </summary>
		void enableFinished();
};