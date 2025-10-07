#include "GameOver.h"
#include "../engine/graphics/DisplayManager.h"
#include "../engine/LogManager.h"
#include "../engine/game/WorldManager.h"
#include "../engine/game/ObjectList.h"
#include "../engine/ResourceManager.h"
#include "../engine/game/EventStep.h"
#include "ProjectileManager.h"
#include "SafeZone.h"

#include "GameStart.h"

GameOver::GameOver() {
	setType("GameOver");
	setSolidness(df::Solidness::SPECTRAL);
	setAltitude(df::MAX_ALTITUDE);
	setPosition(df::Vector((float)(DM.getHorizontalChars() / 2), (float)(DM.getVerticalChars() / 2)));
	setSprite("game-over");
	time_to_live = 120; // 120 frames = 4 seconds at 30 fps
	p_sound = RM.getSound("gameOver");
	if (p_sound == NULL) {
		LM.writeLog("GameOver::GameOver: Warning! Sound not found: game-over");
	}
	else {
		p_sound->play();
	}
}

GameOver::~GameOver() {
	if (p_sound != NULL) {
		p_sound->stop();
	}

	

	df::ObjectList ol = WM.getAllObjects();
	for (int i = 0; i < ol.getCount(); i++) {
		if (ol[i]->getType() == "ProjectileManager")
		{
			ProjectileManager* pm = dynamic_cast<ProjectileManager*>(ol[i]);
			if (pm != NULL)
			{
				SafeZone* sz = pm->getSafeZone();
				if (sz != NULL)
					sz->stopMusic();
			}
		}
		WM.markForDelete(ol[i]);
	}

	new GameStart();
}

int GameOver::eventHandler(const df::Event* p_e) {
	if (p_e->getType() == df::STEP_EVENT) {
		step();
		return 1;
	}
	return 0;
}

void GameOver::step() {
	time_to_live--;
	if (time_to_live <= 0) {
		WM.markForDelete(this);
	}
}