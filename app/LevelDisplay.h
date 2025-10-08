#pragma	once
#include "../engine/game/Object.h"
#include "../engine/graphics/Color.h"

class LevelDisplay : public df::Object 
{
public:
	LevelDisplay();
	int draw() override;
	int eventHandler(const df::Event* p_event) override;

private:
	int level = 1; //current level to display
	const df::Color DEFAULT_COLOR = df::TURQUOISE; //default color of the display
	const df::Color FLASH_COLOR = df::YELLOW; //color to flash when level up
	df::Color current_color = DEFAULT_COLOR; //current color of the display
	bool flashing = false; //is the display currently flashing?
	const float FLASH_DURATION = 5; //duration of the flash in frames
	int flash_time = 0; //current time spent flashing
};