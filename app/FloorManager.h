#pragma once
#include "EventChangeColor.h"
#include "../engine/game/Object.h"

class FloorManager : public df::Object {
	public:
		FloorManager(std::string floor_label);
		int eventHandler(const df::Event* p_e) override;
		int draw() override { return 0; } //not drawable
	private:
		void changeColor(const EventChangeColor* p_color_event);
		bool isSameColor(const df::Color& c1, const df::Color& c2);
		std::string floor_label = "";
};
