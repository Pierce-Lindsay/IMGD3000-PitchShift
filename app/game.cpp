#include "../engine/game/GameManager.h"
#include "../engine/ResourceManager.h"
#include "ProjectileManager.h"
#include "SafeZone.h"
#include <vector>

SafeZone* safeZone = nullptr;
std::vector<float> safePositions = 
{ 20.0f, 40.0f, 10.0f, 30.0f, 10.0f, 20.0f, //3
5.0f, 15.0f, 10.0f, 20.0f, 15.0f, 30.0f, //6
5.0f, 20.0f, 8.0f, 28.0f, 4.0f, 20.0f, //9
5.0f, 8.0f, 4.0f, 8.0f, 3.0f, 7.0f, //12
3.0f, 20.0f, 3.0f,20.0f, 3.0f, 20.0f, //15
8.0f, 16.0f, 24.0f, 32.0f, 40.0f, 30.0f, //18
20.0f, 30.0f, 20.0f, 40.0f, 40.0f, 40.0f, //21
10.0f, 10.0f, 10.0f, 10.0f, 30.0f, 17.0f, //24
10.0f, 10.0f,10.0f, 10.0f, 10.0f, 10.0f, //27 ///////////////////////////
15.0f, 50.0f, 50.0f, 50.0f, 50.0f, 50.0f, //30
60.0f, 50.0f, 50.0f,50.0f, 35.0f, 40.0f, //33
50.0f, 50.0f, 55.0f, 60.0f, 65.0f, 55.0f, //36
70.0f, 70.0f, 70.0f,70.0f, 70.0f, 70.0f, //39//////////////////
8.0f, 16.0f, 24.0f, 32.0f, 40.0f, 30.0f, //42
20.0f, 30.0f, 20.0f, 40.0f, 40.0f, 40.0f, //45
10.0f, 10.0f, 10.0f, 10.0f, 30.0f, 17.0f, //48
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
	//delete safeZone;
    return 0;
}