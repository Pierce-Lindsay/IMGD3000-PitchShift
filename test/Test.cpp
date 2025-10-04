#include "Test.h"
#include <iostream>
#include <thread>
#include "../engine/LogManager.h"
#include "../engine/Clock.h"
#include "../engine/Vector.h"
#include "../engine/ResourceManager.h"
#include "../engine/game/GameManager.h"
#include "../engine/game/Object.h"
#include "../engine/game/ObjectList.h"
#include "../engine/game/EventStep.h"
#include "../engine/game/WorldManager.h"
#include "../engine/graphics/DisplayManager.h"
#include "../engine/graphics/Color.h"
#include "../engine/graphics/Frame.h"
#include "../engine/graphics/Sprite.h"
#include "../engine/Box.h"
#include "../engine/audio/Music.h"
#include "../engine/audio/Sound.h"
#include "../engine/graphics/Animation.h"
#include "../engine/input/EventMouse.h"
#include "../engine/input/EventKeyboard.h"
#include "../engine/game/EventOut.h"
#include "../engine/game/EventCollision.h"
#include "../engine/input/InputManager.h"
#include "../engine/Utility.h"
#include "TestObject.h"
#include "OutObject.h"
#include "TestDrawingObject.h"
#include "TestPlayer.h"
using namespace df;

//helper function just used in this file

/// <summary>
/// Checks whether the two number are within a tolerance of 0.001;
/// </summary>
bool tolerance3(float x, float y)
{
	float t = 0.001;
	return x <= y + t && x >= y - t;
}

Test::Test()
{
	bool logBasePassed = testLogManagerBasicFunctionality();
	if (!logBasePassed)
	{
		std::cout << "Log manager start, failed, faliure to write test info to the log file!" << '\n';
		return;
	}

	//start log manager for testing, all test info sent there
	LM.startUp();
	//push all our tests to our tests vector
	tests.push_back(&Test::testLogManagerLogAfterShutDown);
	tests.push_back(&Test::testLogManagerGoodShutDown);
	tests.push_back(&Test::gameManagerStart);
	tests.push_back(&Test::gameManagerShutDown);
	tests.push_back(&Test::gameManagerPostShutDown);
	tests.push_back(&Test::testLogManagerLogWriting1);
	tests.push_back(&Test::testLogManagerLogWritingEmpty);
	tests.push_back(&Test::testLogManagerLogWritingFlush);
	tests.push_back(&Test::testLogManagerWriteFormated);
	tests.push_back(&Test::testClockStart);
	tests.push_back(&Test::testClockDelta1);
	tests.push_back(&Test::testClockDelta2);
	tests.push_back(&Test::testClockSplit1);
	tests.push_back(&Test::testClockSplit2);
	tests.push_back(&Test::testVectorInit);
	tests.push_back(&Test::testVectorsAdd);
	tests.push_back(&Test::testVectorValueAdd);
	tests.push_back(&Test::testVectorMagnitude);
	tests.push_back(&Test::testVectorNormalizeGood);
	tests.push_back(&Test::testVectorNormalizeBad);
	tests.push_back(&Test::testVectorScale);
	tests.push_back(&Test::objectInitGood);
	tests.push_back(&Test::objectUniqueGood);
	tests.push_back(&Test::objectPosGood);
	tests.push_back(&Test::objectVelocityGood);
	tests.push_back(&Test::objectSpeedGood);
	tests.push_back(&Test::objectDirectionGood);
	tests.push_back(&Test::objectNormalIssue0);
	tests.push_back(&Test::objectNormalIssueNotUnit);
	tests.push_back(&Test::objectPredictPos);
	tests.push_back(&Test::objectVelocityUpdate);
	tests.push_back(&Test::objectAltitudeGood);
	tests.push_back(&Test::objectAltitudeBad);
	tests.push_back(&Test::objectSolidness);
	tests.push_back(&Test::objectListInitGood);
	tests.push_back(&Test::objectListInsertGood);
	tests.push_back(&Test::objectListInsertBad);
	tests.push_back(&Test::objectListIndexBad);
	tests.push_back(&Test::objectListRemoveGood);
	tests.push_back(&Test::objectListRemoveBad);
	tests.push_back(&Test::objectListClear);
	tests.push_back(&Test::eventInit);
	tests.push_back(&Test::eventCorrectType);
	tests.push_back(&Test::eventStepStepGood);
	tests.push_back(&Test::worldManagerInit);
	tests.push_back(&Test::worldManagerShutdown);
	tests.push_back(&Test::worldManagerAddGood);
	tests.push_back(&Test::worldManagerAddBad);
	tests.push_back(&Test::worldManagerUpdate);
	tests.push_back(&Test::worldManagerRemoveGood);
	tests.push_back(&Test::worldManagerRemoveBad);
	tests.push_back(&Test::worldManagerAllOfGetType);
	tests.push_back(&Test::worldManagerOnEvent);
	tests.push_back(&Test::colorDefault);
	tests.push_back(&Test::colorNonDefault);
	tests.push_back(&Test::colorProperSFML);
	tests.push_back(&Test::displayManagerStart);
	tests.push_back(&Test::displayManagerWindowInfo);
	tests.push_back(&Test::displayManagerShutDown);
	tests.push_back(&Test::displayManagerPostShutDown);
	tests.push_back(&Test::utilityCharHeight);
	tests.push_back(&Test::utilityCharWidth);
	tests.push_back(&Test::utilityPixelsToSpaces);
	tests.push_back(&Test::utilitySpacesToPixels);
	tests.push_back(&Test::eventKeyBoardGood);
	tests.push_back(&Test::eventKeyBoardBad);
	tests.push_back(&Test::eventMouseGood);
	tests.push_back(&Test::eventMouseBad);
	tests.push_back(&Test::inputManagerStart);
	tests.push_back(&Test::inputManagerBadStart);
	tests.push_back(&Test::inputManagerShutdown);
	tests.push_back(&Test::eventOut);
	tests.push_back(&Test::objectOutEvent);
	tests.push_back(&Test::eventCollisionCreate);
	tests.push_back(&Test::eventCollisionGood);
	tests.push_back(&Test::positionIntersectGood);
	tests.push_back(&Test::positionIntersectBad);
	tests.push_back(&Test::frameCreate);
	tests.push_back(&Test::frameGood);
	tests.push_back(&Test::frameBad);
	tests.push_back(&Test::spriteCreate);
	tests.push_back(&Test::spriteAdd);
	tests.push_back(&Test::spriteGood);
	tests.push_back(&Test::spriteBad);
	tests.push_back(&Test::animateCreate);
	tests.push_back(&Test::animateRunSpecialSlowdown);
	tests.push_back(&Test::animateRunNormalSlowdown);
	tests.push_back(&Test::soundCreate);
	tests.push_back(&Test::musicCreate);
	tests.push_back(&Test::resourceManagerStartup);
	tests.push_back(&Test::resourceManagerShutdown);
	tests.push_back(&Test::loadSpriteGood);
	tests.push_back(&Test::loadSpriteBad);
	tests.push_back(&Test::unloadSprite);
	tests.push_back(&Test::loadSound);
	tests.push_back(&Test::unloadSound);
	tests.push_back(&Test::loadMusic);
	tests.push_back(&Test::unloadMusic);
	tests.push_back(&Test::boxCreate);
	tests.push_back(&Test::boxEdit);
	tests.push_back(&Test::objectBoxes);
	tests.push_back(&Test::worldBox);
	tests.push_back(&Test::boxIntersectBad);
	tests.push_back(&Test::boxIntersectGood);
	tests.push_back(&Test::getAllCollisionsGood);
	tests.push_back(&Test::getAllCollisionsBad);
	tests.push_back(&Test::getAllCollisionsMulti);
	tests.push_back(&Test::moveHardHardCollisions);
	tests.push_back(&Test::moveHardSoftCollisions);
	tests.push_back(&Test::moveHardSpectralCollisions);
	tests.push_back(&Test::integratedTest);

	int failedTests = runTests();
	if (failedTests == 0)
		LM.writeLog("Test::All tests passed!");
	else
		LM.writeLog("Test::%i tests failed!", failedTests);

	if(GM.isStarted())
		GM.shutDown();
}

int Test::runTests()
{
	int failed = 0;
	for (int i = 0; i < tests.size(); i++)
	{
		//run test and log pass or fail depending on bool
		if ((this->*tests[i])())
			LM.writeLog("Test::Test %d Passed!", i+1);
		else
		{
			LM.writeLog("Test::Test %d Failed!", i+1);
			failed++;
		}
	}
	return failed;
}

//tests a few different basic functionalities
bool Test::testLogManagerBasicFunctionality()
{
	try { //any exceptions is a fail
		int n = LM.startUp();
		LM.setFlush(true); //faster update to log file
		LM.writeLog("Test::Running 'testLogManagerBasicFunctionality': ");
		std::string str = "Test::Test, string!";
		auto writeN = str.length();
		int logN = LM.writeLog(str.c_str());
		bool goodStart = LM.isStarted();
		LM.shutDown();
		if (n == 0 && logN == writeN && goodStart)
			return true;
	}
	catch(...){}
	return false;
}

//these rest assume logmanager is started so they can write to it

bool Test::testLogManagerLogWriting1()
{
	LM.writeLog("Test::Running 'testLogManagerLogWriting1': ");
	std::string str = "Test::Test, string!";
	auto writeN = str.length();
	int logN = LM.writeLog(str.c_str());
	if (logN == writeN)
		return true;
	return false;
}

bool Test::testLogManagerLogWritingEmpty()
{
	LM.writeLog("Test::Running 'testLogManagerLogWritingEmpty': ");
	std::string str = ""; //should just be a newline and return 0
	auto writeN = str.length();
	int logN = LM.writeLog(str.c_str());
	if (logN == writeN)
		return true;
	return false;
}

bool Test::testLogManagerLogWritingFlush()
{
	LM.writeLog("Test::Running 'testLogManagerLogWritingFlush': ");
	try {
		LM.setFlush();
		std::string str = "Test::Should be flushed"; //no asy way to verify
		auto writeN = str.length();
		int logN = LM.writeLog(str.c_str());
		if (logN == writeN) //true if writing worked and no exceptions
			return true;
	}
	catch (...) //return false if any errors thrown
	{}
	return false;	
}

bool Test::testLogManagerLogAfterShutDown()
{
	LM.writeLog("Test::Running 'testLogManagerLogAfterShutDown: ");
	LM.shutDown();
	bool returnB = false;
	if (LM.writeLog("") != 0)
		returnB = true;
	//resart
	LM.startUp();
	return returnB;
}

bool Test::testLogManagerGoodShutDown()
{
	LM.writeLog("Test::Running 'testLogManagerGoodShutDown': ");
	LM.shutDown();
	bool returnB = false;
	if (LM.isStarted() == false)
		returnB = true;
	//resart
	LM.startUp();
	return returnB;
}

bool Test::testLogManagerWriteFormated()
{
	LM.writeLog("Test::Running 'testLogManagerWriteFormated': ");
	try { //test a bucnh of different formattings
		LM.writeLog("Test::Test a bunch of formats!");
		LM.writeLog("Test::Characters: %c %c", 'a', 65);
		LM.writeLog("Test::Decimals: %d %ld", 1977, 650000L);
		LM.writeLog("Test::Preceding with blanks: %10d", 1977);
		LM.writeLog("Test::Preceding with zeros: %010d", 1977);
		LM.writeLog("Test::Some radices: %d %x %o %#x %#o", 100, 100, 100, 100, 100);
		LM.writeLog("Test::floats: %4.2f %+.0e %E", 3.1416, 3.1416, 3.1416);
		LM.writeLog("Test::Width trick: %*d", 5, 10);
		LM.writeLog("Test:: %s", "A string");//true if writing worked and no exceptions
		return true;
	}
	catch (...) //return false if any errors thrown
	{
		return false;
	}
}

bool Test::testClockStart()
{
	LM.writeLog("Test::Running 'testClockStart': ");
	Clock clk;
	long long sleepCount = 1000000;
	LM.writeLog("Test::Planning on sleeping for %lld microseconds after clock start.", sleepCount);
	std::this_thread::sleep_for(std::chrono::microseconds(sleepCount));
	long long delta = clk.delta();
	LM.writeLog("Test::Clock claims slept for %lld microseconds after start.", delta);
	if (delta <= sleepCount + CLOCK_UNCERTAINTY && delta >= sleepCount - CLOCK_UNCERTAINTY)
		return true;
	return false;
}
bool Test::testClockDelta1()
{
	LM.writeLog("Test::Running 'testClockDelta1': ");
	Clock clk;
	clk.delta(); //start new timer
	long long sleepCount = 0;
	LM.writeLog("Test::Planning on sleeping for %lld microseconds after clock start.", sleepCount);
	std::this_thread::sleep_for(std::chrono::microseconds(sleepCount));
	long long delta = clk.delta();
	LM.writeLog("Test::Clock claims slept for %lld microseconds after start.", delta);
	if (delta <= sleepCount + CLOCK_UNCERTAINTY && delta >= sleepCount - CLOCK_UNCERTAINTY)
		return true;
	return false;
}

bool Test::testClockDelta2()
{
	LM.writeLog("Test::Running 'testClockDelta2': ");
	Clock clk;
	clk.delta(); //start new timer
	long long sleepCount = 111110;
	LM.writeLog("Test::Planning on sleeping for %lld microseconds after clock start.", sleepCount);
	std::this_thread::sleep_for(std::chrono::microseconds(sleepCount));
	long long delta = clk.delta();
	LM.writeLog("Test::Clock claims slept for %lld microseconds after start.", delta);
	if (delta <= sleepCount + CLOCK_UNCERTAINTY && delta >= sleepCount - CLOCK_UNCERTAINTY)
		return true;
	return false;
}
bool Test::testClockSplit1()
{
	LM.writeLog("Test::Running 'testClockSplit1: ");
	Clock clk;
	clk.delta(); //start new timer
	long long sleepCount = 100000;
	LM.writeLog("Test::Planning on sleeping for %lld microseconds after clock start.", sleepCount);
	std::this_thread::sleep_for(std::chrono::microseconds(sleepCount));
	long long delta = clk.delta();
	LM.writeLog("Test::Clock claims slept for %lld microseconds after start.", delta);
	LM.writeLog("Test::Split after same amount of time!");
	std::this_thread::sleep_for(std::chrono::microseconds(sleepCount));
	delta = clk.split();	

	if (delta <= sleepCount + CLOCK_UNCERTAINTY && delta >= sleepCount - CLOCK_UNCERTAINTY)
		return true;
	return false;
}
bool Test::testClockSplit2()
{
	LM.writeLog("Test::Running 'testClockSplit2: ");
	Clock clk;
	clk.delta(); //start new timer
	long long sleepCount = 100000;
	LM.writeLog("Test::Planning on sleeping for %lld microseconds after clock start.", sleepCount);
	std::this_thread::sleep_for(std::chrono::microseconds(sleepCount));
	long long delta = clk.split();
	LM.writeLog("Test::Clock claims slept for %lld microseconds after start.", delta);
	LM.writeLog("Test::Split after same amount of time!");
	std::this_thread::sleep_for(std::chrono::microseconds(sleepCount));
	delta = clk.split();
	long long delta2 = clk.delta();
	LM.writeLog("Test::Clock claims slept for total time %lld microseconds after start.", delta);
	if (delta <= 2 * sleepCount + CLOCK_UNCERTAINTY && delta >= 2 * sleepCount - CLOCK_UNCERTAINTY && 
		delta <= delta2 + CLOCK_UNCERTAINTY && delta > delta2-CLOCK_UNCERTAINTY)
		return true;
	return false;
}

bool Test::testVectorInit()
{
	LM.writeLog("Test::Running 'testVectorInit: ");
	Vector v(10, 40);
	if (v.x == 10 && v.y == 40)
		return true;
	return false;
}
bool Test::testVectorsAdd()
{
	LM.writeLog("Test::Running 'testVectorsAdd: ");
	float x = 10;
	float y = 20;
	float z = 50;
	Vector v1(x, y);
	Vector v2(y, z);
	Vector v3 = v1 + v2;

	if (v3.x == x+y && v3.y == y + z)
		return true;
	return false;
}
bool Test::testVectorValueAdd()
{
	LM.writeLog("Test::Running 'testVectorValueAdd: ");
	float x = 10;
	float y = 20;
	float z = 50;
	Vector v1(x, y);
	Vector v2 = v1 + z;

	if (v2.x == x+z && v2.y == y+z)
		return true;
	return false;
}
bool Test::testVectorMagnitude()
{
	LM.writeLog("Test::Running 'testVectorMagnitude: ");
	float x = 10;
	float y = 20;
	Vector v1(x, y);
	float z = v1.getMagnitude();
	float f = z * z;
	float l = (x * x + y * y);
	if (f == l)
		return true;
	return false;
}
bool Test::testVectorNormalizeGood()
{
	LM.writeLog("Test::Running 'testVectorNormalizeGood: ");
	float x = 1;
	float y = 2;
	Vector v1(x, y);
	float z = v1.getMagnitude();
	v1.normalize();
	float exp1 = x / z;
	float exp2 = y / z;
	if (v1.x < exp1 + 0.01 && v1.x > exp1- 0.01 &&
		v1.y < exp2 + 0.01 && v1.y > exp2 - 0.01)
		return true;
	return false;
}
bool Test::testVectorNormalizeBad()
{
	LM.writeLog("Test::Running 'testVectorNormalizeBad: ");
	float x = 0;
	float y = 0;
	Vector v1(x, y);
	float z = v1.getMagnitude();
	try {
		v1.normalize();
		return false;
	}
	catch(...)
	{ return true; } //should catch error
	return false;
}
bool Test::testVectorScale()
{
	LM.writeLog("Test::Running 'testVectorScale: ");
	float x = 1;
	float y = 2;
	float z = 5;
	Vector v1(x, y);
	v1.scale(z);
	if (v1.x == x * z && v1.y == y * z)
		return true;
	return false;
}

bool Test::gameManagerStart()
{
	LM.writeLog("Test::Running 'gameManagerStart': ");
	GM.startUp();
	if (GM.isStarted() && LM.isStarted() && WM.isStarted() && DM.isStarted() && IM.isStarted() && RM.isStarted() && GM.getType() == "GameManager")
		return true;
	return false;
}
bool Test::gameManagerShutDown()
{
	LM.writeLog("Test::Running 'gameManagerShutDown': ");
	GM.shutDown();
	bool success = false;
	if (!GM.isStarted() && !LM.isStarted() && !WM.isStarted() && !DM.isStarted() && !IM.isStarted() && !RM.isStarted())
		success = true;
	if(!LM.isStarted())
		LM.startUp();
	LM.writeLog("Test::Logging was reset from test: ");
	return success;
}
bool Test::gameManagerPostShutDown()
{
	LM.writeLog("Test::Running 'gameManagerPostShutDown': ");
	if (!GM.isStarted())
		GM.startUp();
	GM.shutDown();
	bool success = false;

	if(LM.writeLog("") == -1 && DM.swapBuffers() == -1)//shouldn't work
		success = true;

	if (!LM.isStarted())
		LM.startUp();
	LM.writeLog("Test::Logging was reset from test: ");
	return success;
}

bool Test::objectInitGood()
{
	LM.writeLog("Test::Running 'objectInitGood': ");
	if (!WM.isStarted())//need WM for anything object related
		WM.startUp();
	Object* obj1 = new Object;
	bool b = false;
	if (obj1->getID() == 0 && obj1->getType() == "undefined" && obj1->getPosition().x == 0 && obj1->getPosition().y == 0)
		b = true;
	delete obj1;		
	return b;
}
bool Test::objectUniqueGood()
{
	LM.writeLog("Test::Running 'objectUniqueGood': ");
	if(!WM.isStarted())//need WM for anything object related
		WM.startUp();
	int count = 20;
	Object* base = new Object;
	int baseID = base->getID();
	bool b = true;
	for (int i = 1; i < count; i++)
	{
		Object* obj = new Object;
		if (obj->getID() != i + baseID)
		{
			b = false;
			delete obj;
			break;
		}
		delete obj;
	}
	delete base;
	return b;
}
bool Test::objectPosGood()
{
	LM.writeLog("Test::Running 'objectPosGood': ");
	if (!WM.isStarted())//need WM for anything object related
		WM.startUp();
	Object* obj1 = new Object;
	Object* obj2 = new Object;
	float x = 10;
	float y = 20;
	obj2->setPosition(Vector(x, y));
	Vector v1 = obj1->getPosition();
	Vector v2 = obj2->getPosition();
	bool b = false;
	if (v1.x == 0 && v1.y == 0 && v2.x == x && v2.y == y)
		b = true;
	delete obj1;
	delete obj2;
	return b;
}

bool Test::objectVelocityGood()
{
	LM.writeLog("Test::Running 'objectVelocityGood': ");
	if (!WM.isStarted())//need WM for anything object related
		WM.startUp();
	Object* obj1 = new Object;
	Object* obj2 = new Object;
	float x = 10;
	float y = 20;
	obj2->setVelocity(Vector(x, y));
	Vector v1 = obj1->getVelocity();
	Vector v2 = obj2->getVelocity();
	bool b = false;
	if (v1.x == 0 && v1.y == 0 && v2.x == x && v2.y == y)
		b = true;
	delete obj1;
	delete obj2;
	return b;
}
bool Test::objectVelocityUpdate()
{
	LM.writeLog("Test::Running 'objectVelocityUpdate': ");
	if (!WM.isStarted())//need WM for anything object related
		WM.startUp();
	Object* obj1 = new Object;
	Object* obj2 = new Object;
	float px = -100;
	float py = -30;
	float x = 10;
	float y = 20;
	obj2->setVelocity(Vector(x, y));
	obj1->setPosition(Vector(px, py));
	obj2->setPosition(Vector(px, px));

	WM.update();
	Vector p1 = obj1->getPosition();
	Vector p2 = obj2->getPosition();

	bool b = false;
	if (p1.x == px && p1.y == py && p2.x == px+x && p2.y == px+y)
		b = true;
	delete obj1;
	delete obj2;
	return b;
}

bool Test::objectAltitudeGood()
{
	LM.writeLog("Test::Running 'objectAltitudeGood': ");
	if (!WM.isStarted())//need WM for anything object related
		WM.startUp();
	bool b = false;
	Object* obj1 = new Object;
	Object* obj2 = new Object;

	obj2->setAltitude(MAX_ALTITUDE - 1);

	if (obj2->getAltitude() == MAX_ALTITUDE - 1 && obj1->getAltitude() == MAX_ALTITUDE / 2)
		b = true;
	delete obj1;
	delete obj2;
	return b;
}
bool Test::objectAltitudeBad()
{
	LM.writeLog("Test::Running 'objectAltitudeBad': ");
	if (!WM.isStarted())//need WM for anything object related
		WM.startUp();
	bool b = false;
	Object* obj1 = new Object;
	obj1->setAltitude(MAX_ALTITUDE - 3);
	int try1 = obj1->setAltitude(MIN_ALTITUDE - 1);
	int try2 = obj1->setAltitude(MAX_ALTITUDE + 1);

	if (obj1->getAltitude() == MAX_ALTITUDE - 3 && try1 == -1 && try2 == -1)
		b = true;
	delete obj1;
	return b;
}

bool Test::objectPredictPos()
{
	LM.writeLog("Test::Running 'objectPredictPos': ");
	if (!WM.isStarted())//need WM for anything object related
		WM.startUp();
	bool b = false;
	Object* obj1 = new Object;
	Object* obj2 = new Object;
	Vector pos(2, 2);
	obj1->setPosition(pos);
	obj2->setPosition(pos);
	obj2->setSpeed(10);
	Vector nonUnit = Vector(3, 2);
	obj1->setVelocity(nonUnit);
	Vector expected1 = pos + nonUnit;
	Vector actual1 = obj1->predictPosition();
	Vector actual2 = obj2->predictPosition();
	if (actual1.x == expected1.x && actual1.y == expected1.y &&
		actual2.x == pos.x && actual2.y == pos.y)
		b = true;
	delete obj1;
	delete obj2;
	return b;
}

bool Test::objectSpeedGood()
{
	LM.writeLog("Test::Running 'objectSpeedGood': ");
	if (!WM.isStarted())//need WM for anything object related
		WM.startUp();
	bool b = false;
	Object* obj1 = new Object;
	Object* obj2 = new Object;
	obj2->setVelocity(Vector(2, 1));
	float s = 10;
	float vmag2 = sqrt(5);
	Vector expected_dir(2.0f / vmag2, 1.0f / vmag2);
	obj1->setSpeed(10);
	obj2->setSpeed(-5); // no positive only requirement
	Vector actual_dir = obj2->getDirection();
	if (obj1->getSpeed() == s && float(expected_dir.x) == float(actual_dir.x) && 
		float(expected_dir.y) == float(actual_dir.y) && obj2->getSpeed() == -5 &&
		float(obj2->getVelocity().x) == float(actual_dir.x * -5) 
		&& float(obj2->getVelocity().y) == float(actual_dir.y * -5))
		b = true;
	delete obj1;
	delete obj2;
	return b;
}
bool Test::objectDirectionGood()
{
	LM.writeLog("Test::Running 'objectDirectionGood': ");
	if (!WM.isStarted())//need WM for anything object related
		WM.startUp();
	bool b = false;
	Object* obj1 = new Object;
	Object* obj2 = new Object;
	obj2->setVelocity(Vector(3, -2));
	float vmag2 = sqrt(13);
	Vector expected_dir(3.0f / vmag2, -2.0f / vmag2);
	Vector actual_dir = obj2->getDirection();
	obj1->setDirection(Vector(0, 1));

	if ((float)obj2->getSpeed() == (float)vmag2 && float(expected_dir.x) == float(actual_dir.x) &&
		float(expected_dir.y) == float(actual_dir.y) && obj1->getDirection().x == 0 && obj1->getDirection().y == 1)
		b = true;
	delete obj1;
	delete obj2;
	return b;
}
bool Test::objectNormalIssue0()
{
	LM.writeLog("Test::Running 'objectNormalIssue0': ");
	if (!WM.isStarted())//need WM for anything object related
		WM.startUp();
	bool b = false;
	Object* obj1 = new Object;
	Object* obj2 = new Object;
	obj1->setSpeed(5);
	obj2->setVelocity(Vector(2, -3));
	float vmag2 = sqrt(13);
	obj2->setDirection(Vector(0, 0));

	if (obj1->getSpeed() == 5 && obj1->getVelocity().x == 0 && obj1->getVelocity().y == 0 &&
		obj2->getSpeed() == vmag2 && obj2->getDirection().x == 0 && obj2->getDirection().y ==0 &&
		obj2->getVelocity().x == 0 && obj2->getVelocity().y == 0)
		b = true;
	delete obj1;
	delete obj2;
	return b;
}
bool Test::objectNormalIssueNotUnit()
{
	LM.writeLog("Test::Running 'objectNormalIssueNotUnit': ");
	if (!WM.isStarted())//need WM for anything object related
		WM.startUp();
	bool b = false;
	Object* obj1 = new Object;
	Vector nonUnit = Vector(3, 2);
	Vector unit = nonUnit;
	unit.normalize();
	obj1->setDirection(nonUnit);
	Vector actual = obj1->getDirection();

	if (actual.x == unit.x && actual.y == unit.y)
		b = true;
	delete obj1;
	return b;
}

bool Test::objectSolidness()
{
	LM.writeLog("Test::Running 'objectSolidness': ");
	if (!WM.isStarted())//need WM for anything object related
		WM.startUp();
	bool b = false;
	Object* obj1 = new Object;
	Object* obj2 = new Object;
	Object* obj3 = new Object;
	Solidness second = Solidness::SPECTRAL;
	Solidness third= Solidness::SOFT;
	obj2->setSolidness(second);
	obj3->setSolidness(third);
	Solidness orig = obj1->getSolidness();
	bool isSolid1 = obj1->isSolid();
	bool isSolid2 = obj2->isSolid();
	bool isSolid3 = obj3->isSolid();
	Solidness secondSolid = obj2->getSolidness();

	b = isSolid1 && isSolid3 && !isSolid2 && second == secondSolid && orig == Solidness::HARD;
	delete obj1;
	delete obj2;
	delete obj3;
	return b;
}

bool Test::objectListInitGood()
{
	LM.writeLog("Test::Running 'objectListInitGood': ");
	if (!WM.isStarted())//need WM for anything object related
		WM.startUp();
	//test default init things
	ObjectList list;
	if (list.getCount() == 0 && list.isEmpty())
		return true;
	return false;
}
bool Test::objectListInsertGood()
{
	LM.writeLog("Test::Running 'objectListInsertGood': ");
	if (!WM.isStarted())//need WM for anything object related
		WM.startUp();
	ObjectList list;
	Object* obj1 = new Object;
	Object* obj2 = new Object;;
	//test basic inserts
	int ins1 = list.insert(obj1);
	int ins2 = list.insert(obj2);
	bool b = false;
	if (list.getCount() == 2 && !list.isEmpty() && list[0] == obj1 && list[1] == obj2 && ins1 == 0 && ins2 == 0)
		b = true;
	delete obj1;
	delete obj2;
	return b;
}
bool Test::objectListInsertBad()
{
	LM.writeLog("Test::Running 'objectListInsertBad': ");
	if (!WM.isStarted())//need WM for anything object related
		WM.startUp();
	ObjectList list;
	Object* obj1 = new Object;
	bool b = true;
	for (int i = 0; i < MAX_OBJECTS; i++)
	{
		if (list.insert(obj1) == -1) //normal inserts should be good
		{
			b = false;
			break;
		}	
	}
	
	if (b != false && list.insert(obj1) == -1) //now insert past max, should fail
		b = true;

	delete obj1;
	return b;
}
bool Test::objectListIndexBad()
{
	LM.writeLog("Test::Running 'objectListIndexBad': ");
	if (!WM.isStarted())//need WM for anything object related
		WM.startUp();
	ObjectList list;
	Object* obj1 = new Object;
	//test two different edge cases, should fail both
	list.insert(obj1);
	bool b = false;
	try {
		list[-1];
	}
	catch (...)
	{
		try { 
			list[list.getCount()]; 
		}
		catch (...) {
			b = true;
		}
	}
	delete obj1;
	return b;
}
bool Test::objectListRemoveGood()
{
	LM.writeLog("Test::Running 'objectListRemoveGood': ");
	if (!WM.isStarted())//need WM for anything object related
		WM.startUp();
	ObjectList list;
	Object* obj1 = new Object;
	Object* obj2 = new Object;
	list.insert(obj1);
	list.insert(obj2);
	bool b = false;
	int success = list.remove(obj1);
	if (success ==0 && list.getCount() == 1 && list.find(obj1) == -1 && list.find(obj2) == 0)
		b = true;
	delete obj1;
	delete obj2;
	return b;
}
bool Test::objectListRemoveBad()
{
	LM.writeLog("Test::Running 'objectListRemoveBad': ");
	if (!WM.isStarted())//need WM for anything object related
		WM.startUp();
	ObjectList list;
	Object* obj1 = new Object;
	Object* obj2 = new Object;
	list.insert(obj1);
	bool b = false;
	int shouldFail = list.remove(obj2);
	if (shouldFail == -1 && list.getCount() == 1 && list.find(obj1) == 0 && list.find(obj2) == -1)
		b = true;
	delete obj1;
	delete obj2;
	return b;
}
bool Test::objectListClear()
{
	LM.writeLog("Test::Running 'objectListClear': ");
	if (!WM.isStarted())//need WM for anything object related
		WM.startUp();
	ObjectList list;
	Object* obj1 = new Object;
	Object* obj2 = new Object;
	list.insert(obj1);
	list.insert(obj2);
	list.clear();
	delete obj1;
	delete obj2;
	if (list.getCount() == 0)
		return true;
	return false;
}

bool Test::eventInit()
{
	LM.writeLog("Test::Running 'eventInit': ");
	Event e;
	if (e.getType() == "undefined")
		return true;
	return false;
}
bool Test::eventCorrectType()
{
	LM.writeLog("Test::Running 'eventCorrectType': ");
	EventStep e;
	if (e.getType() == STEP_EVENT)
		return true;
	return false;
}
bool Test::eventStepStepGood()
{
	LM.writeLog("Test::Running 'eventStepStepGood': ");
	int x = 100;
	int y = 50;
	EventStep e(x);
	EventStep e2;
	e2.setStepCount(y);
	if (e.getStepCount() ==x && e.getType() == STEP_EVENT && e2.getStepCount() == y)
		return true;
	return false;
}

bool Test::worldManagerInit()
{
	LM.writeLog("Test::Running 'worldManagerInit': ");
	WM.shutDown();
	if(!WM.isStarted())
		WM.startUp();
	if (WM.getType() == "WorldManager" && WM.getAllObjects().getCount() == 0 && WM.isStarted() == true)
		return true;
	return false;
}

bool Test::worldManagerShutdown()
{
	LM.writeLog("Test::Running 'worldManagerShutdown': ");
	if (!WM.isStarted())
		WM.startUp();
	new Object; //should get added
	int previousCount = WM.getAllObjects().getCount();
	WM.shutDown();
	if (WM.isStarted() == false && WM.getAllObjects().getCount() == 0 && previousCount == 1)
		return true;
	return false;
}

bool Test::worldManagerAddGood()
{
	LM.writeLog("Test::Running 'worldManagerAddGood': ");
	if (!WM.isStarted())
		WM.startUp();
	Object* obj1 = new Object; //should get added
	Object* obj2 = new Object; //should get added
	ObjectList list = WM.getAllObjects();
	bool b = false;
	if (obj1->getID() == list[0]->getID() && obj2->getID() == list[1]->getID() && list.getCount() == 2)
		b =  true;
	WM.shutDown();
	return b;
}
bool Test::worldManagerAddBad()
{
	LM.writeLog("Test::Running 'worldManagerAddBad': ");
	if (!WM.isStarted())
		WM.startUp();
	Object* lastObject = NULL;
	for (int i = 0; i < MAX_OBJECTS; i++)
	{
		lastObject = new Object;
	}
	bool b = false;

	if (WM.insertObject(lastObject) == -1 && WM.getAllObjects().getCount() == MAX_OBJECTS)
		b = true;

	WM.shutDown(); //cleanup
	return b;
}

bool Test::worldManagerUpdate()
{
	LM.writeLog("Test::Running 'worldManagerUpdate': ");
	if (!WM.isStarted())
		WM.startUp();
	Object* o1 = new Object;
	Object* o2= new Object;
	Object* o3 = new Object;

	bool b = false;
	WM.markForDelete(o1);
	WM.markForDelete(o2);
	WM.markForDelete(o3);
	WM.update(); //actually remove
	ObjectList list = WM.getAllObjects();

	if (list.getCount() ==0) //removed properly
		b = true;

	WM.shutDown(); //cleanup
	return b;
}

bool Test::worldManagerRemoveGood()
{
	LM.writeLog("Test::Running 'worldManagerRemoveGood': ");
	if (!WM.isStarted())
		WM.startUp();
	Object* o1 = new Object;
	Object* o2 = new Object;
	Object* o3 = new Object;

	bool b = false;
	WM.markForDelete(o2);
	int beforeCount = WM.getAllObjects().getCount();
	WM.update();
	ObjectList list = WM.getAllObjects();

	if (list.getCount() ==2 && o1->getID() == list[0]->getID() && o3->getID() == list[1] ->getID() && beforeCount == 3) //removed properly
		b = true;

	WM.shutDown(); //cleanup
	return b;
}
bool Test::worldManagerRemoveBad()
{
	LM.writeLog("Test::Running 'worldManagerRemoveBad': ");
	if (!WM.isStarted())
		WM.startUp();
	Object* o1 = new Object;
	Object* o2 = new Object;
	Object* o3 = new Object;

	bool b = false;
	WM.markForDelete(o2);
	int failedMark = WM.markForDelete(o2);
	WM.update();
	ObjectList list = WM.getAllObjects();

	if (list.getCount() == 2 && o1->getID() == list[0]->getID() && o3->getID() == list[1]->getID() && failedMark == -1) //removed properly
		b = true;

	WM.shutDown(); //cleanup
	return b;
}

bool Test::worldManagerAllOfGetType()
{
	LM.writeLog("Test::Running 'worldManagerGetType': ");
	if (!WM.isStarted())
		WM.startUp();
	Object* o1 = new Object;
	Object* o2 = new Object;
	bool b = false;

	int count1 = WM.objectsOfType("undefined").getCount(); //should be 2
	int count2 = WM.objectsOfType("TestObject").getCount(); //should be 0

	TestObject* o3 = new TestObject;

	int count3 = WM.objectsOfType("undefined").getCount(); //should be 2
	int count4 = WM.objectsOfType("TestObject").getCount(); //should be 1


	if (count1 == 2 && count2 == 0 && count3 == 2 && count4 ==1) //identified correct
		b = true;

	WM.shutDown(); //cleanup
	return b;
}

bool Test::worldManagerOnEvent()
{
	LM.writeLog("Test::Running 'worldManagerOnEvent': ");
	if (!WM.isStarted())
		WM.startUp();
	Object* o1 = new Object;
	Object* o2 = new Object;
	bool b = false;
	EventStep step(299);
	int count1 = WM.onEvent(&step); //all ignoring so should be 0

	TestObject* o3 = new TestObject;
	TestObject* o4 = new TestObject;

	int count2 = WM.onEvent(&step); //2 not ignoring so should be 2


	if (count1 == 0 && count2 == 2) //identified correct
		b = true;

	WM.shutDown(); //cleanup
	return b;
}

bool Test::colorDefault()
{
	LM.writeLog("Test::Running 'colorDefault': ");
	auto default_c = Color();
	if(default_c.getR() == 0 && default_c.getG() == 0 &&
		default_c.getB() == 0 && default_c.getA() == 255)
		return true;
	return false;
}
bool Test::colorNonDefault()
{
	LM.writeLog("Test::Running 'colorNonDefault': ");
	uint8_t r = 20;
	uint8_t b = 10;
	uint8_t g = 30;
	uint8_t a = 255;
	auto my_c = Color(r, g, b, a);
	sf::Color sf_c = sf::Color(r, g, b, a);
	if (my_c.getR() == r && my_c.getG() == g && my_c.getB() && my_c.getA() == a &&
		sf_c.r == my_c.getR() && sf_c.g == my_c.getG() && my_c.getB() == sf_c.b && my_c.getA() == sf_c.a)
		return true;
	return false;
}

bool Test::colorProperSFML()
{
	LM.writeLog("Test::Running 'colorProperSFML': ");
	uint8_t r = 20;
	uint8_t b = 10;
	uint8_t g = 30;
	uint8_t a = 255;
	auto my_c = Color(r, g, b, a);
	sf::Color sf_c = sf::Color(r, g, b, a);
	if (my_c.getSFMLColor() == sf_c)
		return true;
	return false;
}

bool Test::displayManagerStart()
{
	LM.writeLog("Test::Running 'displayManagerStart': ");
	if (!DM.isStarted())
		DM.startUp();
	if (DM.isStarted() && DM.getType() == "DisplayManager" && DM.getWindow() != NULL)
		return true;
	return false;
}

bool Test::displayManagerWindowInfo()
{
	LM.writeLog("Test::Running 'displayManagerWindowInfo': ");
	if (!DM.isStarted())
		DM.startUp();
	auto win_size = DM.getWindow()->getSize();

	if(win_size.x == DM.getHorizontalPixels() && win_size.y == DM.getVerticalPixels())
		return true;
	return false;
}

bool Test::displayManagerShutDown()
{
	LM.writeLog("Test::Running 'displayManagerShutDown': ");
	if (!DM.isStarted())
		DM.startUp();
	bool succeeded = true;

	try {
		DM.shutDown();
	}
	catch (...) { succeeded = false; }

	return succeeded && !DM.isStarted();
}
bool Test::displayManagerPostShutDown()
{
	LM.writeLog("Test::Running 'displayManagerPostShutDown': ");
	if (!DM.isStarted())
		DM.startUp();
	bool succeeded = true;

	try {
		DM.shutDown();
	}
	catch (...) { succeeded = false; }

	return succeeded && !DM.isStarted() && DM.getWindow() == NULL && 
		DM.swapBuffers() == -1 && DM.drawCh(df::Vector(0, 0), ' ', WHITE) == -1;
}

bool Test::utilityCharWidth()
{
	LM.writeLog("Test::Running 'utilityCharWidth': ");
	if (!DM.isStarted())
		DM.startUp();

	auto winpx = DM.getHorizontalPixels();
	auto wincx = DM.getHorizontalChars();
	float expected = (float)(winpx / (float)wincx);
	float actual = df::charWidth();
	if (expected < actual + 0.01 && expected > actual - 0.01)
		return true;

	return false;
}
bool Test::utilityCharHeight()
{
	LM.writeLog("Test::Running 'utilityCharHeight': ");
	if (!DM.isStarted())
		DM.startUp();

	auto winpy = DM.getVerticalPixels();
	auto wincy = DM.getVerticalChars();

	float expected = (float)(winpy / (float)wincy);
	float actual = df::charHeight();

	if (expected < actual + 0.01 && expected > actual - 0.01)
		return true;

	return false;
}
bool Test::utilitySpacesToPixels()
{
	LM.writeLog("Test::Running 'utilitySpacesToPixels': ");
	if (!DM.isStarted())
		DM.startUp();

	Vector spaceVec(10, 10);
	float char_width = charWidth();
	float char_height = charHeight();

	Vector expected(spaceVec.x * char_width, spaceVec.y * char_height);
	Vector actual = spacesToPixels(spaceVec);
	if (actual.x < expected.x + 0.01 && actual.x > expected.x - 0.01 && 
		actual.y < expected.y + 0.01 && actual.y > expected.y - 0.01)
		return true;

	return false;
}
bool Test::utilityPixelsToSpaces()
{
	LM.writeLog("Test::Running 'utilityPixelsToSpaces': ");
	if (!DM.isStarted())
		DM.startUp();

	Vector pixVec(1000, 500);
	float char_width = charWidth();
	float char_height = charHeight();

	Vector expected(pixVec.x/char_width, pixVec.y/char_height);
	Vector actual = pixelsToSpaces(pixVec);
	if (actual.x < expected.x + 0.01 && actual.x > expected.x - 0.01 &&
		actual.y < expected.y + 0.01 && actual.y > expected.y - 0.01)
		return true;

	return false;
}

bool Test::eventKeyBoardGood()
{
	LM.writeLog("Test::Running 'eventKeyBoardGood': ");
	EventKeyboard kb1;
	EventKeyboard kb2;
	Keyboard::Key k1 = Keyboard::Key::UNDEFINED_KEY;
	EventKeyboardAction ka1 = EventKeyboardAction::UNDEFINED_KEYBOARD_ACTION;
	Keyboard::Key k2 = Keyboard::Key::D;
	EventKeyboardAction ka2 = EventKeyboardAction::KEY_PRESSED;

	kb2.setKey(k2);
	kb2.setKeyboardAction(ka2);
	return kb1.getKey() == k1 && kb1.getKeyboardAction() == ka1 && kb1.getType() == "keyboard" &&
		kb2.getKey() == k2 && kb2.getKeyboardAction() == ka2 && kb2.getType() == "keyboard";
}
bool Test::eventMouseGood()
{
	LM.writeLog("Test::Running 'eventMouseGood': ");
	EventMouse mouse1;
	EventMouse mouse2;
	Mouse::Button m1 = Mouse::Button::UNDEFINED_MOUSE_BUTTON;
	EventMouseAction ma1 = EventMouseAction::UNDEFINED_MOUSE_ACTION;
	Mouse::Button m2 = Mouse::Button::MIDDLE;
	EventMouseAction ma2 = EventMouseAction::CLICKED;
	Vector v2(10, 20);
	mouse2.setMouseButton(m2);
	mouse2.setMouseAction(ma2);
	mouse2.setMousePosition(v2);
	return mouse1.getMouseButton() == m1 && mouse1.getMouseAction() == ma1 && mouse1.getType() == "mouse" 
		&& mouse1.getMousePosition().x == 0 && mouse1.getMousePosition().y == 0 &&
		mouse2.getMouseButton() == m2 && mouse2.getMouseAction() == ma2 && mouse2.getType() == "mouse" &&
		mouse2.getMousePosition().x == v2.x && mouse2.getMousePosition().y == v2.y;
}
bool Test::eventKeyBoardBad()
{
	LM.writeLog("Test::Running 'eventKeyBoardBad': ");
	EventKeyboard kb1;
	EventKeyboard kb2;
	Keyboard::Key uk = Keyboard::Key::UNDEFINED_KEY;
	EventKeyboardAction uak = EventKeyboardAction::UNDEFINED_KEYBOARD_ACTION;
	Keyboard::Key k1 = static_cast<Keyboard::Key>(101);
	EventKeyboardAction ka1 = static_cast<EventKeyboardAction>(2);
	Keyboard::Key k2 = static_cast<Keyboard::Key>(-2);
	EventKeyboardAction ka2 = static_cast<EventKeyboardAction>(-2);

	kb1.setKey(k1);
	kb1.setKeyboardAction(ka1);
	kb2.setKey(k2);
	kb2.setKeyboardAction(ka2);
	return kb1.getKey() == uk && kb1.getKeyboardAction() == uak  &&
		kb2.getKey() == uk && kb2.getKeyboardAction() == uak;
}
bool Test::eventMouseBad()
{
	LM.writeLog("Test::Running 'eventMouseBad': ");
	EventMouse mouse1;
	EventMouse mouse2;
	Mouse::Button um = Mouse::Button::UNDEFINED_MOUSE_BUTTON;
	EventMouseAction uam = EventMouseAction::UNDEFINED_MOUSE_ACTION;
	Mouse::Button m1 = static_cast<Mouse::Button>(3);
	EventMouseAction ma1 = static_cast<EventMouseAction>(2);
	Mouse::Button m2 = static_cast<Mouse::Button>(-2);
	EventMouseAction ma2 = static_cast<EventMouseAction>(-2);;

	mouse1.setMouseButton(m1);
	mouse1.setMouseAction(ma1);
	mouse2.setMouseButton(m2);
	mouse2.setMouseAction(ma2);
	return mouse1.getMouseButton() == um && mouse1.getMouseAction() == uam &&
		mouse2.getMouseButton() == um && mouse2.getMouseAction() == uam;
}
bool Test::inputManagerStart()
{
	LM.writeLog("Test::Running 'inputManagerStart': ");
	if (!DM.isStarted())
		DM.startUp();
	IM.startUp();
	bool b = false;
	if (IM.isStarted() && IM.getType() == "InputManager")
		b =  true;
	return b;
}

bool Test::inputManagerBadStart()
{
	LM.writeLog("Test::Running 'inputManagerBadStart': ");
	if (IM.isStarted())
		IM.shutDown();
	if (DM.isStarted())
		DM.shutDown();
	int s = IM.startUp();
	bool b = false;
	if (!IM.isStarted() && s == -1)
		b = true;
	return b;
}

bool Test::inputManagerShutdown()
{
	LM.writeLog("Test::Running 'inputManagerShutdown': ");
	if (IM.isStarted())
		IM.shutDown();
	if (!DM.isStarted())
		DM.startUp();
	IM.startUp();
	IM.shutDown();
	DM.shutDown();
	if (IM.isStarted() == false)
		return true;
	return false;
}

bool Test::eventCollisionCreate()
{
	LM.writeLog("Test::Running 'eventCollisionCreate': ");
	if (!WM.isStarted())
		WM.startUp();
	Object* o1 = new Object;
	Object* o2 = new Object;
	Vector pos(10, 5);
	EventCollision ec;
	EventCollision ec2(o1, o2, pos);

	bool b = ec.getPos().x == 0 && ec.getPos().y == 0 && ec.getType() == COLLISION_EVENT &&
		ec.getObject1() == NULL && ec.getObject2() == NULL && ec2.getObject1() == o1 &&
		ec2.getObject2() == o2 && ec2.getPos().x == pos.x && ec2.getPos().y == pos.y;

	delete o1;
	delete o2;
	return b;
}
bool Test::eventCollisionGood()
{
	LM.writeLog("Test::Running 'eventCollisionGood': ");
	if (!WM.isStarted())
		WM.startUp();
	Object* o1 = new Object;
	Object* o2 = new Object;
	Vector pos(10, 5);
	EventCollision ec;
	ec.setObject1(o1);
	ec.setObject2(o2);
	ec.setPos(pos);

	bool b = ec.getObject1() == o1 && ec.getObject2() == o2 
		&& ec.getPos().x == pos.x && ec.getPos().y == pos.y;

	delete o1;
	delete o2;
	return b;
}

bool Test::positionIntersectGood()
{
	LM.writeLog("Test::Running 'positionIntersectGood': ");
	Vector v1(1, 3);
	Vector v2(0, 4);
	Vector v3(-0.5, 4);
	return positionsIntersect(v1, v2) && positionsIntersect(v3, v2);
}
bool Test::positionIntersectBad()
{
	LM.writeLog("Test::Running 'positionIntersectBad': ");
	Vector v1(1, 3);
	Vector v2(6, 4);
	Vector v3(0, 4);
	Vector v4(10, 8);
	return !positionsIntersect(v1, v2) && !positionsIntersect(v3, v2) && !positionsIntersect(v4, v1);
}
bool Test::eventOut()
{
	LM.writeLog("Test::Running 'eventOut': ");
	EventOut out;
	return out.getType() == OUT_EVENT;
}

bool Test::objectOutEvent()
{
	LM.writeLog("Test::Running 'objectOutEvent': ");
	if (!WM.isStarted()) //need world and borders from DM
		WM.startUp();
	if (!DM.isStarted())
		DM.startUp();
	Object* obj = new OutObject;
	Object* obj2 = new OutObject;
	Object* obj3 = new OutObject;
	Object* obj4 = new OutObject;
	Object* obj5 = new OutObject;
	obj->setPosition(Vector(10, 10)); // in
	obj2->setPosition(Vector(-1, 10)); // out
	obj3->setPosition(Vector(0, DM.getHorizontalChars() +1)); // out
	obj4->setPosition(Vector(5, -1)); // out
	obj5->setPosition(Vector(-1, DM.getVerticalChars() + 1)); // out
	WM.update(); //add to deletions
	//
	WM.update(); //delete if in deletions
	int count = WM.objectsOfType("OutObject").getCount(); //should be 1 left
	bool b = count == 1;
	auto list = WM.getAllObjects();
	for (int i = 0; i < list.getCount(); i++)
	{
		delete list[i];
	}
	return b;
}

bool Test::getAllCollisionsGood()
{
	LM.writeLog("Test::Running 'getAllCollisionsGood': ");
	if (!WM.isStarted()) //WM for objects
		WM.startUp();

	Object* obj1 = new Object;
	Object* obj2 = new Object;
	Object* obj3 = new Object;
	Object* obj4 = new Object;
	Object* obj5 = new Object;
	//set colliders as spectral for testing* purposes
	obj1->setPosition(Vector(0, 5));
	obj1->setSolidness(Solidness::SPECTRAL);
	obj3->setSolidness(Solidness::SPECTRAL);
	obj3->setPosition(Vector(10, 10));
	obj3->setVelocity(Vector(-9.1, -9.1));
	obj1->setVelocity(Vector(0, -5));
	obj4->setPosition(Vector(50, -50));
	obj5->setPosition(Vector(40, -50));
	obj4->setSolidness(Solidness::SOFT);
	obj5->setSolidness(Solidness::SPECTRAL);
	obj5->setVelocity(Vector(9.9, 0));
	auto l1 = WM.getCollisions(obj1, obj1->predictPosition());
	auto l2 = WM.getCollisions(obj3, obj3->predictPosition());
	auto l3 = WM.getCollisions(obj5, obj5->predictPosition());
	bool correctOther = l1[0] == obj2 && l1.getCount() == 1;
	bool correctOther2 = l2[0] == obj2 && l2.getCount() == 1;
	bool correctOther3 = l3[0] == obj4 && l3.getCount() == 1;

	bool b = correctOther && correctOther2 && correctOther3;
		
	delete obj1;
	delete obj2;
	delete obj3;
	delete obj4;
	delete obj5;
	return b;
}
bool Test::getAllCollisionsBad()
{
	LM.writeLog("Test::Running 'getAllCollisionsBad': ");
	if (!WM.isStarted()) //WM for objects
		WM.startUp();

	Object* obj1 = new Object;
	Object* obj2 = new Object;
	Object* obj3 = new Object;
	Object* obj4 = new Object;
	Object* obj5 = new Object;
	Object* obj6 = new Object;
	//set colliders as spectral for testing* purposes
	obj1->setPosition(Vector(0, 5));
	obj1->setSolidness(Solidness::SPECTRAL);
	obj3->setSolidness(Solidness::SPECTRAL);
	obj3->setPosition(Vector(10, 10));
	obj3->setVelocity(Vector(-8, -9.5));
	obj1->setVelocity(Vector(0, -7));
	obj4->setPosition(Vector(53, -50));
	obj5->setPosition(Vector(40, -50));
	obj4->setSolidness(Solidness::SOFT);
	obj5->setSolidness(Solidness::SOFT);
	obj5->setVelocity(Vector(9.9, 0));
	obj6->setPosition(Vector(50, -50));
	obj6->setSolidness(Solidness::SPECTRAL);
	auto l1 = WM.getCollisions(obj1, obj1->predictPosition());
	auto l2 = WM.getCollisions(obj3, obj3->predictPosition());
	auto l3 = WM.getCollisions(obj5, obj5->predictPosition());
	bool correctOther =  l1.getCount() == 0;
	bool correctOther2 = l2.getCount() == 0;
	bool correctOther3 =  l3.getCount() == 0;

	bool b = correctOther && correctOther2 && correctOther3;

	delete obj1;
	delete obj2;
	delete obj3;
	delete obj4;
	delete obj5;
	delete obj6;
	return b;
}

bool Test::getAllCollisionsMulti()
{
	LM.writeLog("Test::Running 'getAllCollisionsMulti': ");
	if (!WM.isStarted()) //WM for objects
		WM.startUp();

	Object* obj1 = new Object;
	Object* obj2 = new Object;
	Object* obj3 = new Object;
	Object* obj4 = new Object;
	//set colliders as spectral for testing* purposes
	obj1->setPosition(Vector(0, 0.5));
	obj1->setSolidness(Solidness::SPECTRAL);
	obj3->setPosition(Vector(10, 10));
	obj3->setVelocity(Vector(-9.5, -9.5));
	obj4->setPosition(Vector(0, 0.25));
	obj4->setSolidness(Solidness::SOFT);

	auto l1 = WM.getCollisions(obj3, obj3->predictPosition());
	bool b = l1.find(obj2) >= 0 && l1.find(obj4) >= 0 && l1.getCount() == 2;

	delete obj1;
	delete obj2;
	delete obj3;
	delete obj4;
	return b;
}

bool Test::moveHardSoftCollisions()
{
	LM.writeLog("Test::Running 'moveHardSoftCollisions': ");
	if (!WM.isStarted()) //WM for objects
		WM.startUp();

	Object* obj1 = new Object;
	Object* obj2 = new Object;
	Object* obj3 = new Object;

	//set colliders as spectral for testing* purposes

	obj1->setSolidness(Solidness::SOFT);
	obj2->setSolidness(Solidness::HARD);
	obj3->setPosition(Vector(10, 10));
	obj3->setVelocity(Vector(-9.5, -9.5));
	obj3->setSolidness(Solidness::SOFT);

	bool b = WM.moveObject(obj3, obj3->predictPosition()) == 0;

	b = b && obj3->getPosition().x == 0.5 && obj3->getPosition().y == 0.5;

	delete obj1;
	delete obj2;
	delete obj3;
	return b;
}
bool Test::moveHardHardCollisions()
{
	LM.writeLog("Test::Running 'moveHardHardCollisions': ");
	if (!WM.isStarted()) //WM for objects
		WM.startUp();

	Object* obj1 = new Object;
	Object* obj2 = new Object;
	Object* obj3 = new Object;

	//set colliders as spectral for testing* purposes
	obj1->setSolidness(Solidness::SOFT);
	obj2->setSolidness(Solidness::HARD);
	obj3->setPosition(Vector(10, 10));
	obj3->setVelocity(Vector(-9.5, -9.5));
	obj3->setSolidness(Solidness::HARD);

	bool b = WM.moveObject(obj3, obj3->predictPosition()) == -1;

	b = b && obj3->getPosition().x == 10 && obj3->getPosition().y == 10;

	delete obj1;
	delete obj2;
	delete obj3;
	return b;
}
bool Test::moveHardSpectralCollisions()
{
	LM.writeLog("Test::Running 'moveHardSpectralCollisions': ");
	if (!WM.isStarted()) //WM for objects
		WM.startUp();

	Object* obj1 = new Object;
	Object* obj2 = new Object;
	Object* obj3 = new Object;
	Object* obj4 = new Object;
	Object* obj5 = new Object;

	//set colliders as spectral for testing* purposes
	obj1->setSolidness(Solidness::SOFT);
	obj2->setSolidness(Solidness::HARD);
	obj3->setPosition(Vector(10, 10));
	obj3->setVelocity(Vector(-9.5, -9.5));
	obj3->setSolidness(Solidness::SPECTRAL);

	obj4->setPosition(Vector(30, 10));
	obj4->setVelocity(Vector(-2, -2));

	obj5->setPosition(Vector(28, 8));
	obj5->setSolidness(Solidness::SPECTRAL);

	bool b = WM.moveObject(obj3, obj3->predictPosition()) == 0;
	b = b && WM.moveObject(obj4, obj4->predictPosition()) == 0;

	b = b && obj3->getPosition().x == 0.5 && obj3->getPosition().y == 0.5
		&& obj4->getPosition().x == 28 && obj4->getPosition().y == 8;

	delete obj1;
	delete obj2;
	delete obj3;
	delete obj4;
	delete obj5;
	return b;
}

bool Test::frameCreate()
{
	LM.writeLog("Test::Running 'frameCreate': ");
	Frame f;
	int x = 100;
	int y = 100;
	std::string str = "str";
	Frame f2(x, y, str);

	return f.getHeight() == 0 && f.getWidth() == 0 && f.getString() == "" &&
		f2.getHeight() == y && f2.getWidth() == x && f2.getString() == str;
}
bool Test::frameGood()
{
	LM.writeLog("Test::Running 'frameGood': ");
	std::string str = "hello world!";
	int x = 6;
	int y = 2;
	Frame f(x, y, str);

	int x2 = 3;
	int y2 = 1;
	std::string str2 = "str";
	Frame f2(x2, y2, str2);

	if (!DM.isStarted())
		DM.startUp();

	int attempt = f.draw(Vector(5, 5), WHITE);
	int attempt2 = f2.draw(Vector(5, 5), WHITE);

	return attempt == 0 && attempt2 == 0;
}
bool Test::frameBad()
{
	LM.writeLog("Test::Running 'frameBad': ");
	std::string str = "hello world!";
	int x = 6; //wrong dimensions
	int y = 3;
	Frame f(x, y, str);

	Frame f2; //empty

	Frame f3;

	f3.setHeight(-1);
	f3.setWidth(-1); //shouldn't go through (should stay 0)

	if (!DM.isStarted())
		DM.startUp();

	int attempt = f.draw(Vector(5, 5), WHITE);
	int attempt2 = f2.draw(Vector(5, 5), WHITE);

	return attempt == -1 && attempt2 == -1 && f3.getHeight() ==0 && f3.getWidth() == 0;
}

bool Test::spriteCreate()
{
	LM.writeLog("Test::Running 'spriteCreate': ");
	int max = 10;
	Sprite s(max);
	return s.getFrameCount() == 0 && s.getSlowdown() == 1 && s.getHeight() == 0 && s.getLabel() == "undefined" && s.getWidth() == 0;
}
bool Test::spriteAdd()
{
	LM.writeLog("Test::Running 'spriteAdd': ");
	int max = 2;
	Sprite s(max);
	Frame f;

	std::string str = "hello world!";
	int x = 6;
	int y = 2;
	Frame f2(x, y, str);

	int a1 = s.addFrame(f);
	int a2 = s.addFrame(f2);
	int a3 = s.addFrame(f); //should fail
	int c = s.getFrameCount();
	int w1 = s.getFrame(0).getWidth();
	int w2 = s.getFrame(1).getWidth();

	return a1 == 0 && a2 == 0 && a3 == -1 && c == 2 && w1 == 0 && w2 == x;
}
bool Test::spriteGood()
{
	LM.writeLog("Test::Running 'spriteGood': ");
	if (!DM.isStarted())
		DM.startUp();
	int max = 2;
	Sprite s(max);
	std::string str = "hello world!";
	int x = 6;
	int y = 2;
	Frame f(x, y, str);
	s.setColor(RED);
	s.setLabel(str);

	//all of these should be valid and work
	int a1 = s.addFrame(f);
	int a2 = s.addFrame(f);
	int a3 = s.draw(0, Vector(1, 2));
	int a4 = s.draw(1, Vector(1, 2));

	return a1 == 0 && a2 == 0 && a3 == 0 && a4 == 0 && s.getLabel() == str;
}
bool Test::spriteBad()
{
	LM.writeLog("Test::Running 'spriteBad': ");
	if (!DM.isStarted())
		DM.startUp();
	int max = 2;
	Sprite s(max);
	std::string str = "hello world!";
	int x = 6; //incorrect dimensions
	int y = 3;
	Frame f(x, y, str);
	Frame f2; //cant draw empty

	int a1 = s.addFrame(f);
	int a2 = s.addFrame(f2);
	//these shoudl fail
	int a3 = s.draw(0, Vector(1, 2));
	int a4 = s.draw(1, Vector(1, 2));

	return a1 == 0 && a2 == 0 && a3 == -1 && a4 == -1;
}

bool Test::animateCreate()
{
	LM.writeLog("Test::Running 'animateCreate': ");
	Animation a;
	Animation a2;
	Sprite s(100);
	std::string n2 = "hello";
	a2.setSprite(&s);
	a2.setName(n2);
	a2.setIndex(3);
	a2.setSlowdownCount(2);
	return a.getName() == "undefined" && a.getIndex() == 0 && a.getSlowdownCount() == 0 && a.getSprite() == NULL &&
		a2.getName() == n2 && a2.getIndex() == 3 && a2.getSlowdownCount() == 2 && a2.getSprite() == &s;
}
bool Test::animateRunSpecialSlowdown()
{
	LM.writeLog("Test::Running 'animateRunSpecialSlowdown': ");
	Animation a;
	Animation a2;
	Frame f;
	Sprite s(100);
	s.setSlowdown(0);
	s.addFrame(f);
	s.addFrame(f);
	Sprite s2(100);
	s2.setSlowdown(1);
	a.setSprite(&s);
	s2.addFrame(f);
	s2.addFrame(f);
	a2.setSprite(&s2);

	int n0 = a2.getIndex(); //start on 0
	a.draw(Vector(0, 0));
	int n1 = a.getIndex();
	a2.draw(Vector(0, 0));
	int n2 = a2.getIndex();
	a.draw(Vector(0, 0));
	int n3 = a.getIndex();
	a2.draw(Vector(0, 0));
	int n4 = a2.getIndex();

	return n0 == 0 && n1 == 0 && n2 == 1 && n3 == 0 && n4 == 0;
}
bool Test::animateRunNormalSlowdown()
{
	LM.writeLog("Test::Running 'animateRunNormalSlowdown': ");
	Animation a;
	Animation a2;
	Animation aNull; //shoul return -1 on draw
	Frame f;
	Sprite s(100);
	s.setSlowdown(2);
	s.addFrame(f);
	s.addFrame(f);
	Sprite s2(100);
	s2.setSlowdown(3);
	a.setSprite(&s);
	s2.addFrame(f);
	s2.addFrame(f);
	a2.setSprite(&s2);
	int shouldFail = aNull.draw(Vector(0, 0));

	int an0 = a.getIndex(); //start on 0
	a.draw(Vector(0, 0));
	int an1 = a.getIndex();
	a.draw(Vector(0, 0));
	int an2 = a.getIndex();
	a.draw(Vector(0, 0));
	int an3 = a.getIndex();

	int a2n0 = a2.getIndex(); //start on 0
	a2.draw(Vector(0, 0));
	int a2n1 = a2.getIndex();
	a2.draw(Vector(0, 0));
	int a2n2 = a2.getIndex();
	a2.draw(Vector(0, 0));
	int a2n3 = a2.getIndex();


	return shouldFail == -1 && an0 == 0 && a2n0 == 0 && an1 == 0 && a2n1 == 0 && an2 == 1 && a2n2 == 0 &&
		an3 == 1 && a2n3 == 1;
}
	 
bool Test::soundCreate()
{
	LM.writeLog("Test::Running 'soundCreate': ");
	Sound sNull;
	Sound s;
	std::string fire = "fire";
	int n = s.loadSound("fire.wav");
	s.setLabel(fire);
	return n == 0 && sNull.getLabel() == "undefined" && sNull.getSound() == NULL && s.getLabel() == fire &&
		s.getSound() != NULL;
}
	 
bool Test::musicCreate()
{
	LM.writeLog("Test::Running 'musicCreate': ");
	Music mNull;
	Music m;
	std::string l = "music";
	int n = m.loadMusic("start-music.wav");
	m.setLabel(l);
	return n == 0 && mNull.getLabel() == "undefined" && m.getLabel() == l &&
		m.getMusic() != NULL;
}
	 
bool Test::resourceManagerStartup()
{
	LM.writeLog("Test::Running 'resourceManagerStartup': ");
	bool b = false;
	if(!RM.isStarted())
		RM.startUp();
	if (RM.isStarted() && RM.getType() == "ResourceManager")
		b = true;
	return b;
}
bool Test::resourceManagerShutdown()
{
	LM.writeLog("Test::Running 'resourceManagerShutdown': ");
	if (!RM.isStarted())
		RM.startUp();

	std::string sp_l = "sprite";
	std::string s_l = "sound";
	std::string m_l = "music";
	int good1 = RM.loadSprite("laser-spr.txt", sp_l);
	int good2 = RM.loadSound("fire.wav", s_l);
	int good3 = RM.loadMusic("start-music.wav", m_l);

	RM.shutDown();
	return !RM.isStarted() && RM.getSprite(sp_l) == NULL && RM.getSound(s_l) == NULL && RM.getMusic(m_l) == NULL &&
		good1 == 0 && good2 == 0 && good3 == 0; //need to actually upload properly
}
bool Test::loadSpriteGood()
{
	LM.writeLog("Test::Running 'loadSpriteGood': ");
	if (!RM.isStarted())
		RM.startUp();

	bool b = false;

	std::string l1 = "s1";
	std::string l2 = "s2";
	std::string l3 = "s3";
	int good1 = RM.loadSprite("laser-spr.txt", l1);
	int good2 = RM.loadSprite("powerup-spr.txt", l2);
	int good3 = RM.loadSprite("good-test1.txt", l3);

	//confirm sprite header and body (hardcoded based on sprite files)
	Sprite* sp = RM.getSprite(l2);
	bool b_frame1 = sp->getFrameCount() == 3;
	bool b_w1 = sp->getWidth() == 1;
	bool b_h1 = sp->getHeight() == 3;
	bool b_slow1 = sp->getSlowdown() == 16;
	bool b_color1 = sp->getColor().getR() == 255;
	bool b_f1_1 = sp->getFrame(0).getString() == "^||";
	bool b_f1_2 = sp->getFrame(1).getString() == "+||";
	bool b_f1_3 = sp->getFrame(2).getString() == "-||";
	bool good4 = b_frame1 && b_w1 && b_h1 && b_slow1 && b_color1  && b_f1_1 && b_f1_2 && b_f1_3;

	Sprite* sp2 = RM.getSprite(l1);
	bool b_frame2 = sp2->getFrameCount() == 2;
	bool b_w2 = sp2->getWidth() == 4;
	bool b_h2 = sp2->getHeight() == 1;
	bool b_slow2 = sp2->getSlowdown() == 10;
	bool b_color2 = sp2->getColor().getG() == 255;
	bool b_f2_1 = sp2->getFrame(0).getString() == "----";
	bool b_f2_2 = sp2->getFrame(1).getString() == "--- ";

	bool good5 = b_frame2 && b_w2 && b_h2 && b_slow2 && b_color2 && b_f2_1 && b_f2_2;

	b = good1 == 0 && good2 == 0 && good3 == 0 && good5 && good4 && //need to actually upload properly
		RM.getSprite(l1) != NULL && RM.getSprite(l2) != NULL && RM.getSprite(l3) != NULL;
	RM.shutDown(); //clear dependencies
	return b;
}
bool Test::loadSpriteBad()
{
	LM.writeLog("Test::Running 'loadSpriteBad': ");
	if (!RM.isStarted())
		RM.startUp();

	bool b = false;

	std::string l1 = "s1";
	std::string l2 = "s2";
	std::string l3 = "s3";
	std::string l4 = "s4";
	int bad1 = RM.loadSprite("invalid-frame-count1.txt", l1);
	int bad2 = RM.loadSprite("invalid-frame-count2.txt", l2);
	int bad3 = RM.loadSprite("invalid-widths.txt", l3);
	int bad4 = RM.loadSprite("invalid-heights.txt", l4);
	int bad5 = RM.loadSprite("efwefwf.txt", "hi"); //giberish

	b = bad1 == -1 && bad2 == -1 && bad3 == -1 && bad4 == -1 && bad5 == -1;
	RM.shutDown(); //clear dependencies
	return b;
}
bool Test::unloadSprite()
{
	LM.writeLog("Test::Running 'unloadSprite': ");
	if (!RM.isStarted())
		RM.startUp();
	bool b = false;

	std::string l1 = "s1";
	std::string l2 = "s2";
	std::string l3 = "s3";
	int good1 = RM.loadSprite("laser-spr.txt", l1);
	int good2 = RM.loadSprite("powerup-spr.txt", l2);
	int good3 = RM.loadSprite("good-test1.txt", l3);
	Sprite* before1 = RM.getSprite(l1);
	Sprite* before2 = RM.getSprite(l2);
	Sprite* before3 = RM.getSprite(l3);
	int good4 = RM.unloadSprite(l2);
	Sprite* after1 = RM.getSprite(l1);
	Sprite* after2 = RM.getSprite(l2);
	Sprite* after3 = RM.getSprite(l3);

	b = good1 == 0 && good2 == 0 && good3 == 0 && good4 == 0 &&
		before1 != NULL && before2 != NULL && before3 != NULL &&
		after1 != NULL && after2 == NULL && after3 != NULL;
	RM.shutDown(); //clear dependencies
	return b;
}
	 
bool Test::loadSound()
{
	LM.writeLog("Test::Running 'loadSound': ");
	if (!RM.isStarted())
		RM.startUp();

	bool b = false;

	std::string l1 = "s1";
	std::string l2 = "s2";
	std::string l3 = "s3";
	int good1 = RM.loadSound("fire.wav", l1);
	int good2 = RM.loadSound("explode.wav", l2);
	int good3 = RM.loadSound("game-over.wav", l3);


	b = good1 == 0 && good2 == 0 && good3 == 0 && //need to actually upload properly
		RM.getSound(l1) != NULL && RM.getSound(l2) != NULL && RM.getSound(l3) != NULL;
	RM.shutDown(); //clear dependencies
	return b;
}
bool Test::unloadSound()
{
	LM.writeLog("Test::Running 'unloadSound': ");
	if (!RM.isStarted())
		RM.startUp();

	bool b = false;

	std::string l1 = "s1";
	std::string l2 = "s2";
	std::string l3 = "s3";
	int good1 = RM.loadSound("fire.wav", l1);
	int good2 = RM.loadSound("explode.wav", l2);
	int good3 = RM.loadSound("game-over.wav", l3);
	Sound* before1 = RM.getSound(l1);
	Sound* before2 = RM.getSound(l2);
	Sound* before3 = RM.getSound(l3);
	int good4 = RM.unloadSound(l1);
	Sound* after1 = RM.getSound(l1);
	Sound* after2 = RM.getSound(l2);
	Sound* after3 = RM.getSound(l3);

	b = good1 == 0 && good2 == 0 && good3 == 0 && good4 == 0 &&
		before1 != NULL && before2 != NULL && before3 != NULL &&
		after1 == NULL && after2 != NULL && after3 != NULL;
	RM.shutDown(); //clear dependencies
	return b;
}
	 
bool Test::loadMusic()
{
	LM.writeLog("Test::Running 'loadMusic': ");
	if (!RM.isStarted())
		RM.startUp();

	bool b = false;

	std::string l1 = "m1";
	int good1 = RM.loadMusic("start-music.wav", l1);

	b = good1 == 0 && //need to actually upload properly
		RM.getMusic(l1) != NULL;
	RM.shutDown(); //clear dependencies
	return b;
}
bool Test::unloadMusic()
{
	LM.writeLog("Test::Running 'unloadMusic': ");
	if (!RM.isStarted())
		RM.startUp();

	bool b = false;

	std::string l1 = "m1";
	int good1 = RM.loadMusic("start-music.wav", l1);
	Music* before1 = RM.getMusic(l1);
	int good2 = RM.unloadMusic(l1);
	Music* after1 = RM.getMusic(l1);
	b = good1 == 0 && good2 == 0 && //need to actually upload properly
		before1 != NULL && after1 == NULL;
	RM.shutDown(); //clear dependencies
	return b;
}
	 
bool Test::boxCreate()
{
	LM.writeLog("Test::Running 'boxCreate': ");
	Box b;
	Vector v1(10, 20);
	float x = 5;
	float y = 6;
	Box b2(v1, x, y);

	return b.getCorner().x == 0 && b.getCorner().y == 0 && b.getHorizontal() == 0 && b.getVertical() == 0 &&
		b2.getCorner().x == v1.x && b2.getCorner().y == v1.y && b2.getHorizontal() == x && b2.getVertical() == y;

}
bool Test::boxEdit()
{
	LM.writeLog("Test::Running 'boxEdit': ");
	Box b;
	Vector v1(10, 20);
	float x = 5;
	float y = 6;
	b.setCorner(v1);
	b.setHorizontal(x);
	b.setVertical(y);

	return b.getCorner().x == v1.x && b.getCorner().y == v1.y && b.getHorizontal() == x && b.getVertical() == y;
}
bool Test::objectBoxes() // mainly tests enimation getBox method
{
	LM.writeLog("Test::Running 'objectBoxes': ");
	if (!RM.isStarted())
		RM.startUp();
	if (!WM.isStarted())//need WM for anything object related
		WM.startUp();

	Object* obj1 = new Object;
	Object* obj2 = new Object;
	Object* obj3 = new Object;
	RM.loadSprite("good-test1.txt", "s1");
	RM.loadSprite("powerup-spr.txt", "s2");
	obj2->setSprite("s1");
	obj3->setSprite("s2");
	Sprite* sp3 = RM.getSprite("s2");
	float width = sp3->getWidth();
	float height = sp3->getHeight();

	Box b1 = obj1->getBox();
	Box b2 = obj2->getBox();
	Box b3 = obj3->getBox();

	bool good1 = tolerance3(b1.getCorner().x, -0.5) && tolerance3(b1.getCorner().y, -0.5) &&
		tolerance3(b1.getHorizontal(), 0.99) && tolerance3(b1.getVertical(), 0.99);

	bool good2 = tolerance3(b2.getCorner().x, -0.5) && tolerance3(b2.getCorner().y, -0.5) &&
		tolerance3(b2.getHorizontal(), 0.99) && tolerance3(b2.getVertical(), 0.99);

	bool good3 = tolerance3(b3.getCorner().x, -0.5 * width) && tolerance3(b3.getCorner().y, -0.5 * height) &&
		tolerance3(b3.getHorizontal(), width * 0.99) && tolerance3(b3.getVertical(), height * 0.99);

	bool b = good1 && good2 && good3;
	RM.shutDown();
	delete obj1;
	delete obj2;
	delete obj3;

	return b;
}
	 
bool Test::worldBox()
{
	LM.writeLog("Test::Running 'worldBox': ");
	if (!WM.isStarted())//need WM for anything object related
		WM.startUp();
	
	Object* obj1 = new Object;
	Object* obj2 = new Object;
	Vector v1(10, -5);
	Vector p1(3, 4);
	Vector v2(-0.5, -5);
	Vector p2(3, 4);

	obj1->setPosition(p1);
	obj1->setBox(Box(v1, 10, 20));
	obj2->setBox(Box(v2, 2, 5));

	Box b1 = getWorldBox(obj1);
	Box b2 = getWorldBox(obj2, p2);

	Vector predict1 = v1 + p1;
	Vector predict2 = v2 + p2;


	bool good1 = b1.getCorner().x == predict1.x && b1.getCorner().y == predict1.y &&
		b1.getHorizontal() == 10 && b1.getVertical() == 20;

	bool good2 = b2.getCorner().x == predict2.x && b2.getCorner().y == predict2.y &&
		b2.getHorizontal() == 2 && b2.getVertical() == 5;


	bool b = good1 && good2;

	delete obj1;
	delete obj2;

	return b;
}
	 
bool Test::boxIntersectGood()
{
	LM.writeLog("Test::Running 'boxIntersectGood': ");
	Box b1(Vector(0, 0), 1, 1);
	Box b2(Vector(0.5, 0.5), 1, 1);
	bool good1 = boxIntersectsBox(b1, b2) && boxIntersectsBox(b2, b1);
	Box b3(Vector(0, 0), 1, 1);
	Box b4(Vector(1, 1), 3, 3);
	bool good2 = boxIntersectsBox(b3, b4) && boxIntersectsBox(b4, b3);

	Box b5(Vector(5, 5), 10, 5);
	Box b6(Vector(7, 7), 2, 1);
	bool good3 = boxIntersectsBox(b5, b6) && boxIntersectsBox(b6, b5);
	Box b7(Vector(0, 0), 6, 1);
	Box b8(Vector(0.5, -2), 1, 6);
	bool good4 = boxIntersectsBox(b7, b8) && boxIntersectsBox(b8, b7);

	Box b9(Vector(0, 0), 2, 3);
	Box b10(Vector(2, 1.5), 1, 1);
	bool good5 = boxIntersectsBox(b9, b10) && boxIntersectsBox(b10, b9);
	Box b11(Vector(0, 0), 2, 3);
	Box b12(Vector(0, 0), 2, 3);
	bool good6 = boxIntersectsBox(b11, b12) && boxIntersectsBox(b12, b11);

	return good1 && good2 && good3 && good4 && good5 && good6;
}
bool Test::boxIntersectBad()
{
	LM.writeLog("Test::Running 'boxIntersectBad': ");
	Box b1(Vector(0, 0), 1, 1);
	Box b2(Vector(2, 2), 1, 1);
	bool good1 = !boxIntersectsBox(b1, b2) && !boxIntersectsBox(b2, b1);
	Box b3(Vector(-10, 1), 1, 1);
	Box b4(Vector(-10, 10), 3, 3);
	bool good2 = !boxIntersectsBox(b3, b4) && !boxIntersectsBox(b4, b3);
	Box b5(Vector(5, 5), 2, 2);
	Box b6(Vector(7.1, 7.1), 2, 1);
	bool good3 = !boxIntersectsBox(b5, b6) && !boxIntersectsBox(b6, b5);
	return good1 && good2 && good3;
}
	 
/// <summary>
/// Ultimate test that runs the game and tests everything with eachother. 
/// Uses Test Objects to interact with the game.
/// </summary>
bool Test::integratedTest()
{
	if (DM.isStarted())
		DM.shutDown();
	if (RM.isStarted())
		RM.shutDown();
	if (GM.isStarted())
		GM.shutDown();

	bool b = true;
	LM.writeLog("Test::Running 'integratedTest': ");
	if (!GM.isStarted()) //fails if my TestObject or the engine throws any errors
		GM.startUp();

	//add sprite and music and sound resources

	RM.loadSprite("chunk-spr.txt", "chunk");
	RM.loadSprite("laser-spr.txt", "laser");
	RM.loadSprite("powerup-spr.txt", "powerup");
	RM.loadSprite("frazzle-spr.txt", "frazzle");

	RM.loadMusic("start-music.wav", "music1");

	RM.loadSound("fire.wav", "fire");
	RM.loadSound("explode.wav", "explode");


	//create a bunch of test objects to test justifications/altitudes
	Vector pos1(60, 2);
	Vector pos2(60, 3);
	Vector pos3(60, 4);
	Vector pos4(60, 5);
	TestDrawingObject* t1 = new TestDrawingObject("left justified");
	TestDrawingObject* t2 = new TestDrawingObject("right justified");
	TestDrawingObject* t3 = new TestDrawingObject("center justified");
	TestDrawingObject* t4 = new TestDrawingObject("x");
	t1->setPosition(pos1);
	t2->setPosition(pos2);
	t3->setPosition(pos3);
	t4->setPosition(pos4);
	t1->setColor(GREEN);
	t2->setColor(df::RED);
	t3->setColor(df::BLUE);
	t1->setJust(df::Justification::LEFT);
	t2->setJust(df::Justification::RIGHT);
	t3->setJust(df::Justification::CENTER);
	t1->setAltitude(MAX_ALTITUDE);
	t2->setAltitude(MAX_ALTITUDE);
	t3->setAltitude(MAX_ALTITUDE);
	t4->setAltitude(MAX_ALTITUDE);

	Vector pos5(10, 2);
	Vector pos6(15, 2);
	Vector pos7(20, 2);
	Vector pos8(25, 2);
	Vector pos9(30, 2);
	TestDrawingObject* t5 = new TestDrawingObject("altitude4");
	TestDrawingObject* t6 = new TestDrawingObject("altitude3");
	TestDrawingObject* t7 = new TestDrawingObject("altitude2");
	TestDrawingObject* t8 = new TestDrawingObject("altitude1");
	TestDrawingObject* t9 = new TestDrawingObject("altitude0");
	t5->setPosition(pos5);
	t6->setPosition(pos6);
	t7->setPosition(pos7);
	t8->setPosition(pos8);
	t9->setPosition(pos9);
	t5->setColor(df::RED);
	t6->setColor(df::BLUE);
	t7->setColor(df::GREEN);
	t8->setColor(df::GRAY);
	t9->setColor(df::PURPLE);
	t5->setAltitude(MAX_ALTITUDE);
	t6->setAltitude(MAX_ALTITUDE-1);
	t7->setAltitude(MAX_ALTITUDE-2);
	t7->setAltitude(MAX_ALTITUDE-2);
	t8->setAltitude(MAX_ALTITUDE-3);
	t9->setAltitude(MAX_ALTITUDE-4);

	TestDrawingObject* t10 = new TestDrawingObject("Altitude test below");
	TestDrawingObject* t11 = new TestDrawingObject("Justification test below");
	Vector pos10(7, 0);
	Vector pos11(45, 0);
	t10->setPosition(pos10);
	t11->setPosition(pos11);
	//simulated player
	new TestPlayer;

	try {
		GM.run();
	}
	catch (...) { b = false; }
	GM.shutDown();
	return b;
}