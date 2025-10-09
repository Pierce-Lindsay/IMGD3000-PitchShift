#pragma once
#include "../engine/game/Object.h"

class Title : public df::Object {
	public:
		Title();
		int eventHandler(const df::Event* p_e) override;
};