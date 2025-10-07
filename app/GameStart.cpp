#include "GameStart.h"
#include "../engine/input/EventKeyboard.h"
#include "../engine/graphics/DisplayManager.h"
#include "../engine/LogManager.h"
#include "../engine/game/WorldManager.h"
#include "../engine/game/GameManager.h"
#include "../engine/ResourceManager.h"

#include "FloorManager.h"
#include "ProjectileManager.h"
#include "Player.h"
#include "Portal.h"
#include "Floor.h"
#include "SafeZone.h"
#include "Countdown.h"
#include <vector>

SafeZone* safeZone = nullptr; //needs to be handled by someone else
FloorManager* floorManager = nullptr;
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

GameStart::GameStart() {
	setType("GameStart");
	setSolidness(df::Solidness::SPECTRAL);
	setAltitude(df::MAX_ALTITUDE);
	setPosition(df::Vector((float)(DM.getHorizontalChars() / 2), (float)(DM.getVerticalChars() / 2)));
	setSprite("game-start");

	p_music = RM.getMusic("startMusic");
	if (p_music == NULL) {
		LM.writeLog("GameStart::GameStart: Warning! Music not found: startMusic");
	}
	playMusic();
}

int GameStart::eventHandler(const df::Event* p_e) {
	if (p_e->getType() == df::KEYBOARD_EVENT) {
		df::EventKeyboard* p_keyboard_event = (df::EventKeyboard*)p_e;
		switch (p_keyboard_event->getKey()) {
		case df::Keyboard::Key::P: 			// play
			start();
			break;
		case df::Keyboard::Key::Q:			// quit
			GM.setGameOver();
			break;
		default:
			break;
		}
		return 1;
	}
	return 0;
}

void GameStart::playMusic() {
	if (p_music != NULL) {
		p_music->play(true);
	}
}

void GameStart::start() {
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
	floorManager = new FloorManager("floor");

	new ProjectileManager(safeZone);

	new Player;

	if(p_music != NULL) {
		p_music->stop();
	}

	Countdown* cd = new Countdown;
	cd->start();

	WM.markForDelete(this); // self delete
}