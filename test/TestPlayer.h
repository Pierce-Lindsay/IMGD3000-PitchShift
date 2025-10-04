#pragma once
#include "../engine/game/Object.h"
#include "../engine/audio/music.h"
/// <summary>
/// Class for a pretend user player that inherits from object that tests a few functionalities.
/// Also the major piece of code that works the integrated test.
/// </summary>
class TestPlayer : public df::Object
{
private:
	bool collisionTestStarted = false;
	Object* reticle;
	Object* startGameText;
	df::Music* start_music = NULL;

public:
	/// <summary>
	/// Create and set type.
	/// </summary>
	TestPlayer();

	/// <summary>
	/// Handle step event.
	/// </summary>
	int eventHandler(const df::Event* p_e) override;

	int draw() override;

};