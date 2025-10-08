#pragma once
#include "../engine/Event.h"

const std::string LEVEL_UP_EVENT = "level_up";
/// <summary>
/// Level up event, sent when the player levels up.
/// </summary>
class EventLevelUp : public df::Event
{
public:
	EventLevelUp(int level = 1);

	/// <summary>
	/// Set the level of the level up(the new level).
	/// </summary>
	void setLevel(int level); 

	/// <summary>
	/// Get the level the game just changed to.
	/// </summary>
	int getLevel() const;
private:
	int level = 1;
};