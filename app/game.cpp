#include "../engine/game/GameManager.h"
#include "../engine/graphics/DisplayManager.h"
#include "../engine/ResourceManager.h"
#include "ProjectileManager.h"
#include "Player.h"
#include "Portal.h"
#include "Floor.h"

/// <summary>
/// Initialize resources for the game(sprites, sounds, music).
/// </summary>
void initResources()
{
	RM.loadSprite("projectile1.txt", "projectile1");
	RM.loadSprite("projectile2.txt", "projectile2");
	RM.loadSprite("floor.txt", "floor");
	RM.loadSprite("portal.txt", "portal");
	RM.loadSprite("chunk-spr.txt", "player");
}

/// <summary>
/// Initializes objects required by the game.
/// </summary>
void initObjects()
{
	new ProjectileManager;

	new Player;

	// Create 2 portals, one going to higher pitch, one to lower pitch
	Portal* p1 = new Portal;
	p1->setToHigherPitch(true);
	p1->setPosition(df::Vector((float)(DM.getHorizontalChars() - 3), (float)(DM.getVerticalChars() - 5)));

	Portal* p2 = new Portal;
	p2->setToHigherPitch(false);
	p2->setPosition(df::Vector(3.0f, (float)(DM.getVerticalChars() - 5)));

	for (int i = 0; i < 5; i++) {
		Floor* p_floor = new Floor;
		p_floor->setPosition(df::Vector((float)(i * 16 + 8), (float)(DM.getVerticalChars() - 2)));
	}
}

int main() {

   // Test();

    GM.startUp();
	initResources();
	initObjects();
	GM.run();
    return 0;
}