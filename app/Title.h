#pragma once
#include "../engine/game/Object.h"

/// <summary>
/// The beautiful title that animates on the start menu.
/// </summary>
class Title : public df::Object {
	public:
		Title();
		int eventHandler(const df::Event* p_e) override;
};