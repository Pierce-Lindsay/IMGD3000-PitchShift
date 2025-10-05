#include "../engine/game/GameManager.h"
#include "../engine/ResourceManager.h"
#include "ProjectileManager.h"
#include "SafeZone.h"
#include <vector>

SafeZone* safeZone = nullptr;
std::vector<float> safePositions = 
{ 1.0f, 3.0f, 5.0f, 7.0f, 9.0f, 
11.0f, 13.0f, 15.0f, 17.0f, 19.0f, 
21.0f, 23.0f, 25.0f, 27.0f, 29.0f, 
31.0f, 33.0f, 35.0f, 37.0f, 39.0f,
38.0f, 37.0f, 35.0f, 33.0f, 31.0f,
29.0f, 27.0f, 25.0f, 23.0f, 21.0f,
19.0f, 17.0f, 15.0f, 13.0f, 11.0f,
9.0f, 7.0f, 5.0f, 3.0f, 1.0f,
}; //every half second for ... seconds

/// <summary>
/// Initialize resources for the game(sprites, sounds, music).
/// </summary>
void initResources()
{
	RM.loadSprite("projectile1.txt", "projectile1");
	RM.loadSprite("projectile2.txt", "projectile2");
	RM.loadMusic("phantom.wav", "mainMusic");
}

/// <summary>
/// Initializes objects required by the game.
/// </summary>
void initObjects()
{
	safeZone = new SafeZone(safePositions, 0.5f, RM.getMusic("mainMusic"));
	new ProjectileManager(safeZone);
}

int main() {

   // Test();

    GM.startUp();
	initResources();
	initObjects();
	GM.run();
	delete safeZone;
    return 0;
}