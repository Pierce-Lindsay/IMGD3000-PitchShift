#include <vector>
#include <functional>
#pragma once

/// <summary>
/// Class for testing the game engine, constructor runs all game engine tests
/// </summary>
class Test
{
public:
	/// <summary>
	/// Creates a test class and runs all the tests in the constructor;
	/// </summary>
	Test();

private:
	std::vector <bool(Test::*)()> tests;
	//needed because sleep is inconsistent
	const long long CLOCK_UNCERTAINTY = 100000; //microseconds
	/// <summary>
	/// Runs tests and returns number of failed tests.
	/// </summary>
	int runTests();

	bool testLogManagerBasicFunctionality();
	bool testLogManagerLogWriting1();
	bool testLogManagerLogWritingEmpty();
	bool testLogManagerLogWritingFlush();
	bool testLogManagerLogAfterShutDown();
	bool testLogManagerGoodShutDown();
	bool gameManagerStart();
	bool gameManagerShutDown();
	bool gameManagerPostShutDown();
	bool testLogManagerWriteFormated();

	bool testClockStart();
	bool testClockDelta1();
	bool testClockDelta2();
	bool testClockSplit1();
	bool testClockSplit2();

	bool testVectorInit();
	bool testVectorsAdd();
	bool testVectorValueAdd();
	bool testVectorMagnitude();
	bool testVectorNormalizeGood();
	bool testVectorNormalizeBad();
	bool testVectorScale();

	bool objectInitGood();
	bool objectUniqueGood();
	bool objectPosGood();
	bool objectVelocityGood();
	bool objectPredictPos();
	bool objectVelocityUpdate();
	bool objectAltitudeGood();
	bool objectAltitudeBad();
	bool objectSpeedGood();
	bool objectDirectionGood();
	bool objectNormalIssue0();
	bool objectNormalIssueNotUnit();
	bool objectSolidness();

	bool objectListInitGood();
	bool objectListInsertGood();
	bool objectListInsertBad();
	bool objectListIndexBad();
	bool objectListRemoveGood();
	bool objectListRemoveBad();
	bool objectListClear();

	bool eventInit();
	bool eventCorrectType();
	bool eventStepStepGood();

	bool worldManagerInit();
	bool worldManagerShutdown();
	bool worldManagerAddGood();
	bool worldManagerAddBad();
	bool worldManagerRemoveGood();
	bool worldManagerRemoveBad();
	bool worldManagerUpdate();
	bool worldManagerAllOfGetType();
	bool worldManagerOnEvent();

	bool colorDefault();
	bool colorNonDefault();
	bool colorProperSFML();

	bool displayManagerStart();
	bool displayManagerWindowInfo();
	bool displayManagerShutDown();
	bool displayManagerPostShutDown();

	bool utilityCharWidth();
	bool utilityCharHeight();
	bool utilitySpacesToPixels();
	bool utilityPixelsToSpaces();

	bool eventKeyBoardGood();
	bool eventMouseGood();
	bool eventKeyBoardBad();
	bool eventMouseBad();

	bool inputManagerStart();
	bool inputManagerBadStart();
	bool inputManagerShutdown();

	bool eventOut();
	bool objectOutEvent();
	bool eventCollisionCreate();
	bool eventCollisionGood();
	bool positionIntersectGood();
	bool positionIntersectBad();
	bool getAllCollisionsGood();
	bool getAllCollisionsBad();
	bool getAllCollisionsMulti();
	bool moveHardSoftCollisions();
	bool moveHardHardCollisions();
	bool moveHardSpectralCollisions();

	bool frameCreate();
	bool frameGood();
	bool frameBad();

	bool spriteCreate();
	bool spriteAdd();
	bool spriteGood();
	bool spriteBad();

	bool animateCreate();
	bool animateRunSpecialSlowdown();
	bool animateRunNormalSlowdown();

	bool soundCreate();
	bool musicCreate();

	bool resourceManagerStartup();
	bool resourceManagerShutdown();
	bool loadSpriteGood();
	bool loadSpriteBad();
	bool unloadSprite();

	bool loadSound();
	bool unloadSound();

	bool loadMusic();
	bool unloadMusic();

	bool boxCreate();
	bool boxEdit();
	bool objectBoxes();

	bool worldBox();

	bool boxIntersectGood();
	bool boxIntersectBad();


	/// <summary>
	/// Ultimate test that runs the game and tests everything with eachother. 
	/// Uses the TestObject class to interact with the game on step events.
	/// </summary>
	bool integratedTest();
};