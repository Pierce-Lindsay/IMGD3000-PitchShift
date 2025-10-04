#pragma once
#include "../Event.h"

namespace df {

	static const std::string STEP_EVENT = "step";

	/// <summary>
	/// An event that is triggered every step of the game.
	/// </summary>
	class EventStep : public Event 
	{
	private:
		long long step_count = 0; //loop iteration number

	public:
		/// <summary>
		/// Create EventStep with step_count of 0.
		/// </summary>
		EventStep();

		/// <summary>
		/// Create EventStep with the given step_count.
		/// </summary>
		EventStep(long long init_step_count);

		/// <summary>
		/// Set the step count of the EventStep.
		/// </summary>
		void setStepCount(long long new_step_count);

		/// <summary>
		/// Get the current step count of the EventStep.
		/// </summary>
		long long getStepCount() const;
	};
}