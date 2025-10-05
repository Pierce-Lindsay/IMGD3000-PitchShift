#include "../engine/game/GameManager.h"
#include "../engine/ResourceManager.h"
#include "ProjectileManager.h"

/// <summary>
/// Initialize resources for the game(sprites, sounds, music).
/// </summary>
void initResources()
{
	RM.loadSprite("projectile1.txt", "projectile1");
	RM.loadSprite("projectile2.txt", "projectile2");
}

/// <summary>
/// Initializes objects required by the game.
/// </summary>
void initObjects()
{
	new ProjectileManager;
}

int main() {

   // Test();

    GM.startUp();
	initResources();
	initObjects();
	GM.run();
    return 0;
}