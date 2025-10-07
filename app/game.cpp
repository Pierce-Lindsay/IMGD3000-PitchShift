#include "../engine/game/GameManager.h"
#include "../engine/graphics/DisplayManager.h"
#include "../engine/ResourceManager.h"
#include "ProjectileManager.h"
#include "Player.h"
#include "Portal.h"
#include "Floor.h"
#include "SafeZone.h"
#include <vector>

SafeZone* safeZone = nullptr;
std::vector<float> safePositions = 
{ 30.0f, 60.0f, 20.0f, 30.0f, 60.0f, 30.0f, //6
10.0f, 30.0f, 10.0f, 70.0f, 20.0f, 10.0f, //12
30.0f, 50.0f, 70.0f, 10.0f,50.0f, 20.0f, //18
70.0f,10.0f, 70.0f, 10.0f, 20.0f, 40.0f, //24 //////
30.0f, 60.0f, 70.0f, 10.0f, 30.0f, 30.0f, //30
50.0f, 70.0f, 10.0f, 70.0f, 40.0f, 65.0f, //36
70.0f, 30.0f, 20.0f, 40.0f, 40.0f, 65.0f, //42
10.0f, 50.0f, 70.0f, 10.0f, 30.0f, 10.0f, //48
20.0f, 10.0f,10.0f, 65.0f, 45.0f, 10.0f, //54 
65.0f, 45.0f, 10.0f, 50.0f, 70.0f, 20.0f, //60
60.0f, 70.0f, 20.0f,50.0f, 20.0f,60.0f, //66
40.0f,20.0f, 40.0f, 60.0f, 75.0f, 60.0f, //72
 30.0f, 60.0f, 20.0f, 30.0f, 60.0f, 30.0f, //78
 30.0f, 60.0f, 20.0f, 30.0f, 60.0f, 70.0f, //84
30.0f, 5.0f, 20.0f, 40.0f, 70.0f, 10.0f, //90
50.0f, 75.0f, 15.0f, 40.0f //94
}; //every half second for ... seconds

/// <summary>
/// Initialize resources for the game(sprites, sounds, music).
/// </summary>
void initResources()
{
	RM.loadSprite("projectile1.txt", "projectile1");
	RM.loadSprite("projectile2.txt", "projectile2");
	RM.loadSprite("floor.txt", "floor");
	RM.loadSprite("turquoise-portal.txt", "turquoise-portal");
	RM.loadSprite("orange-portal.txt", "orange-portal");
	RM.loadSprite("chunk-spr.txt", "player");
	RM.loadMusic("phantom.wav", "mainMusic");
}

/// <summary>
/// Initializes objects required by the game.
/// </summary>
void initObjects()
{
	// Create 2 portals, one going to higher pitch, one to lower pitch
	Portal* p1 = new Portal;
	p1->setToHigherPitch(true);
	p1->setPosition(df::Vector((float)(DM.getHorizontalChars() - 2), (float)(DM.getVerticalChars() - 5)));
	p1->setSprite("turquoise-portal");

	Portal* p2 = new Portal;
	p2->setToHigherPitch(false);
	p2->setPosition(df::Vector(1.0f, (float)(DM.getVerticalChars() - 5)));
	p2->setSprite("orange-portal");

	for (int i = 0; i < 5; i++) {
		Floor* p_floor = new Floor;
		p_floor->setPosition(df::Vector((float)(i * 16 + 8), (float)(DM.getVerticalChars() - 2)));
	}
	safeZone = new SafeZone(safePositions, 1.0f, RM.getMusic("mainMusic"));
	new ProjectileManager(safeZone);

	new Player;
}

int main() {

   // Test();

    GM.startUp();
	initResources();
	initObjects();
	GM.run();
	//delete safeZone;
    return 0;
}