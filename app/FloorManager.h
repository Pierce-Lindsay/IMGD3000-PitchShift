#pragma once
#include "EventChangeColor.h"
#include "../engine/game/Object.h"

/// <summary>
/// Handles the color change of the floors.
/// </summary>
class FloorManager : public df::Object {
	public:

		FloorManager(std::string floor_label);

		int eventHandler(const df::Event* p_e) override;

		int draw() override { return 0; } //not drawable

	private:
		/// <summary>
		/// Change the color of the floor according to the event(lower or higher pitch)
		/// </summary>
		void changeColor(const EventChangeColor* p_color_event);

		/// <summary>
		/// Determine if two colors are equal.
		/// </summary>
		bool isSameColor(const df::Color& c1, const df::Color& c2);
		std::string floor_label = ""; //label of the floor sprite
};
