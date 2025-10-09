#pragma once
#include "../engine/game/Object.h"
#include "../engine/graphics/Color.h"

/// <summary>
/// Handles the current score accumulated by the player and
/// their high score. Writes new high score if applicable when games ends.
/// </summary>
class ScoreDisplay : public df::Object
{
public:
	ScoreDisplay();

	int eventHandler(const df::Event* p_e) override;

	int draw()  override;

private:
	long long current_score = 0;
	long long high_score = 0;
	const std::string SCORE_SAVE_FILE = "assets/save_file.txt";
	const df::Color CURRENT_COLOR = df::YELLOW;
	const df::Color HIGH_COLOR = df::ORANGE;
};