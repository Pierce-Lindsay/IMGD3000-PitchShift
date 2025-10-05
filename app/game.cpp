#include "../engine/game/GameManager.h"
#include "../engine/graphics/DisplayManager.h"
#include "../engine/ResourceManager.h"
#include "ProjectileManager.h"
#include "Player.h"
#include "Portal.h"

/// <summary>
/// Initialize resources for the game(sprites, sounds, music).
/// </summary>
void initResources()
{
	RM.loadSprite("projectile1.txt", "projectile1");
	RM.loadSprite("projectile2.txt", "projectile2");
	RM.loadSprite("chunk-spr.txt", "player");
	RM.loadSprite("frazzle-spr.txt", "portal");
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
	p1->setPosition(df::Vector((float)(DM.getHorizontalChars() - 1), (float)(DM.getVerticalChars() - 5)));

	Portal* p2 = new Portal;
	p2->setToHigherPitch(false);
	p2->setPosition(df::Vector(1.0f, (float)(DM.getVerticalChars() - 5)));
}

int main() {

   // Test();

    GM.startUp();
	initResources();
	initObjects();
	GM.run();
    return 0;
}