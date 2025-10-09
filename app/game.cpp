#include "../engine/game/GameManager.h"
#include "../engine/ResourceManager.h"
#include "../engine/graphics/DisplayManager.h"
#include "GameStart.h"

std::string floor_label("floor");

/// <summary>
/// Initialize resources for the game(sprites, sounds, music).
/// </summary>
void initResources()
{
	RM.loadSprite("projectile2.txt", "projectile2");
	RM.loadSprite("floor.txt", floor_label);
	RM.loadSprite("turquoise-portal.txt", "turquoise-portal");
	RM.loadSprite("orange-portal.txt", "orange-portal");
	RM.loadSprite("player.txt", "player");
	RM.loadSprite("game-start.txt", "game-start");
	RM.loadSprite("game-over.txt", "game-over");
	RM.loadSprite("right-arrow.txt", "right-arrow");
	RM.loadSprite("left-arrow.txt", "left-arrow");
	RM.loadSprite("title.txt", "title");
	RM.loadMusic("phantom.wav", "mainMusic");
	RM.loadMusic("shop.wav", "startMusic");
	RM.loadSound("game-over.wav", "gameOver");
	RM.loadSound("explode.wav", "explode");
	RM.loadSound("level_up.wav", "levelUp");
	RM.loadSound("teleport.wav", "teleport");

	sf::Image icon;
	if (icon.loadFromFile("assets/PitchShiftImage.png"))
	{
		
		// Apply it as the window & taskbar icon
		DM.getWindow()->setIcon(icon);
	}


}

/// <summary>
/// Initializes objects required by the game.
/// </summary>
void initObjects()
{
	new GameStart;
}

int main() {

   // Test();

    GM.startUp();
	initResources();
	initObjects();
	GM.run();
    return 0;
}