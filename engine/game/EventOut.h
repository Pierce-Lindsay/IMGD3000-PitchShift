#pragma once
#include "../Event.h"

namespace df {

	const std::string OUT_EVENT = "out";

	class EventOut : public Event {

	public:
		/// <summary>
		/// Create a new Out Event.
		/// </summary>
		EventOut();
	};
}