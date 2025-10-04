#pragma once
#include "../engine/game/Object.h"
#include "../engine/Clock.h"

/// <summary>
/// Class for a pretend user object that inherits from object that tests a few functionalities.
/// Also the major piece of code that works the integrated test.
/// </summary>
class TestObject : public df::Object
{
private:
	int test_step_count = -1; //to test step event
	const int test_length = 300; //10 second test
	df::Clock clock;
	//functions to call during the integrated test to ensure proper conditions
	df::Clock clock2;

	//objects we spawn in and manipulate
	Object* o1 = NULL;
	Object* o2 = NULL;
	Object* o3 = NULL;

	/// <summary>
	/// Called once per frame, tests on different info.
	/// </summary>
	void onFrameTest();

public:
	/// <summary>
	/// Create and set type.
	/// </summary>
	TestObject();

	/// <summary>
	/// Handle step event.
	/// </summary>
	int eventHandler(const df::Event* p_e) override;

};