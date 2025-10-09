#include "ScoreDisplay.h"
#include "EventLevelUp.h"
#include "../engine/graphics/DisplayManager.h"
#include "../engine/LogManager.h"
#include "EventGameEnd.h"
#include <iostream>
#include <fstream>

ScoreDisplay::ScoreDisplay(Difficulty d)
{
	setType("score-display");
	score_multi = static_cast<long long>(d);
	setAltitude(df::MAX_ALTITUDE);
	setSolidness(df::Solidness::SPECTRAL);

	//first check if score file exists
	std::ifstream read(SCORE_SAVE_FILE);
	if (!read.is_open()) //not open so create file and write 0
	{
		std::ofstream ostream(SCORE_SAVE_FILE);
		if (ostream.is_open())
		{
			ostream << 0 << std::endl;
			ostream.close();
		}
		
		high_score = 0;
	}
	else
	{
		std::string high = "";
		read >> high;
		high_score = std::stoll(high);
		read.close();
	}

}


int ScoreDisplay::eventHandler(const df::Event* p_e)
{
	if (p_e->getType() == LEVEL_UP_EVENT)
	{
		const EventLevelUp* e = dynamic_cast<const EventLevelUp*>(p_e);
		current_score += e->getLevel() * score_multi; //add level to current score
	}
	else if (p_e->getType() == GAME_END_EVENT) //update high score if applicable
	{
		if (current_score > high_score) //only overwrite if score is better
		{
			std::ofstream ostream(SCORE_SAVE_FILE);
			if (ostream.is_open())
			{
				ostream << current_score << std::endl;
				ostream.close();
			}
			else
			{
				LM.writeLog("ScoreDisplay::eventHandler::Error writing to save file!");
			}
		}
	}
	return 0;
}

int ScoreDisplay::draw()
{
	std::string high = "High Score: " + std::to_string(high_score);
	std::string current = "Score: " + std::to_string(current_score);

	//draw current score
	int d1 = DM.drawString(df::Vector(1, 2), current, df::Justification::RIGHT, CURRENT_COLOR);
	// 
	//draw high score
	int d2 = DM.drawString(df::Vector(1, 3), high, df::Justification::RIGHT, HIGH_COLOR);
	if (d1 == -1 || d2 == -1)
		return -1;
	return 0;
}