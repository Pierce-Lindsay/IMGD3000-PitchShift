#pragma once
#include "../engine/game/Object.h"
#include "../engine/Event.h"
/// <summary>
/// Class for a pretend user object that inherits from object that tests drawing functionalities.
/// A major piece of code that works the integrated test.
/// </summary>
class SpriteObject : public df::Object
{
private:

public:
	/// <summary>
	/// Create with given sprite.
	/// </summary>
	SpriteObject(std::string sprite_label);

	/// <summary>
	/// Handle step event.
	/// </summary>
	int eventHandler(const df::Event* p_e) override;

};