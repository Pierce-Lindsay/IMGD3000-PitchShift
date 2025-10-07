#pragma once
#include "../engine/game/Object.h"
#include "../engine/graphics/Color.h"
#include "EventChangeColor.h"

class Floor : public df::Object {
	private:
		// Change color based on teleport event
		void changeColor(const EventChangeColor* p_color_event);

		// Check if two colors are the same
		bool isSameColor(df::Color c1, df::Color c2);
	public:
		Floor();
		~Floor();
		int eventHandler(const df::Event* p_e) override;
};