#pragma once
#include "../engine/game/Object.h"
#include "../engine/game/EventOut.h"

/// <summary>
/// Class for object to get out events.
/// </summary>
class OutObject : public df::Object
{

public:
	/// <summary>
	/// Create and set type.
	/// </summary>
	OutObject();

	/// <summary>
	/// Handle step event.
	/// </summary>
	int eventHandler(const df::Event* p_e) override;

};