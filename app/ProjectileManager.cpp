#include "ProjectileManager.h"
#include "../engine/game/WorldManager.h"
#include "../engine/graphics/DisplayManager.h"
#include "../engine/LogManager.h"
#include "../engine/game/EventStep.h"
#include "../engine/Utility.h"
#include "../engine/graphics/Color.h"
#include "../engine/game/GameManager.h"
#include "EventCountdownFinished.h"
#include <array>

std::array<std::string, 2> sprite_labels = {"projectile2" }; //potential sprites for projectiles


ProjectileManager::ProjectileManager(SafeZone* safeZone) {
	setType("ProjectileManager");
	setSolidness(df::Solidness::SPECTRAL);
	this->safeZone = safeZone;
}
ProjectileManager::~ProjectileManager() 
{
	//safeZone is handled by this
	if(safeZone) {
		delete safeZone;
		safeZone = nullptr;
	}
}

int ProjectileManager::draw() {
	return 0; //not drawable
}

int ProjectileManager::eventHandler(const df::Event* p_event) {
	if(safeZone == nullptr) {
		LM.writeLog("ProjectileManager::eventHandler: Warning! No safe zone provided, cannot spawn projectiles.");
		return 0;
	}


	if (p_event->getType() == COUNTDOWN_FINISHED_EVENT)
	{
		//sending event means its done, this is our notification
		const EventCountdownFinished* p_countdown_event = dynamic_cast<const EventCountdownFinished*>(p_event);
		if (p_countdown_event) {
			setSpawing(true);
			LM.writeLog("ProjectileManager::eventHandler: Countdown finished, starting spawning and safe zone.");
		}
		return 1;
	}
	else if (p_event->getType() == df::STEP_EVENT) 
	{
		const df::EventStep* p_step = dynamic_cast<const df::EventStep*>(p_event);

		float curTime = 0;

		if((safeZone->hasStarted() && spawning) && 
			(initial_offset && (curTime = safeZone->getMusicTime()) - lastSpawnTime >= INITIAL_OFFSET  || (curTime = safeZone->getMusicTime()) - lastSpawnTime >= SPAWN_INTERVAL))
		{
			if (initial_offset) initial_offset = false; //only apply initial offset once

			safeZone->update();
			if (safeZone->isFinished()) 
			{
				spawning = false;
				LM.writeLog("ProjectileManager::eventHandler: Safe zone finished, stopping spawning.");
				return 1;
			}
			else
			{
				createProjectiles(); //only create if not finished
				lastSpawnTime = curTime;
			}
		}
		return 1;
	}
	return 0;
}

void ProjectileManager::createProjectile(float xPos, float yPos) {
	//create a projectile at the given x position
	//float speed = 5 + (rand() % 10 + 1)/80.0f * GM.getDeltaTime();
	float speed = 0.55;
	//int sprite_roll = rand() % sprite_labels.size();
	std::string sprite_label = sprite_labels[0];	
	Projectile* p = new Projectile(df::Vector(xPos, yPos), df::RED, speed, sprite_label);

	if (p == NULL) {
		LM.writeLog("ProjectileManager::createProjectile: Warning! Could not create projectile");
		return;
	}
	//LM.writeLog("ProjectileManager::createProjectile: Created projectile %d at x: %f, speed: %f", p->getID(), xPos, speed);
}


void ProjectileManager::createProjectiles() {

	if(safeZone == nullptr) {
		LM.writeLog("ProjectileManager::createProjectiles: Warning! No safe zone provided, cannot spawn projectiles.");
		return;
	}

	float safeZoneCenter = float(safeZone->getSafeZone());
	float leftStart = 5;
	float rightEnd = float(DM.getHorizontalChars() - 3);

	if(safeZoneCenter < leftStart || safeZoneCenter > rightEnd) {
		LM.writeLog("ProjectileManager::createProjectiles: Warning! Safe zone center out of bounds, cannot spawn projectiles.");
		return;
	}

	float leftEnd = safeZoneCenter - (safeZone->getWidth() / 2);
	if (leftEnd < leftStart) leftEnd = leftStart;
	float rightStart = safeZoneCenter + (safeZone->getWidth() / 2);
	if (rightStart > rightEnd) rightStart = rightEnd;


	LM.writeLog("ProjectileManager::createProjectiles::Safe zone pos: %f", safeZoneCenter);

	int leftSpawnCount = (leftEnd - leftStart) / 5; //every other position
	int rightSpawnCount = (rightEnd - rightStart) /5; //every other position

	//we want spikes to drop sooner when further away from safe zone
	float yPos = 0;
	for (int i = 0; i < leftSpawnCount; i++) {
		float xPos = float(leftStart + i * 5 + 1); //+1 to avoid spawning at 0
		createProjectile(xPos,0);
		yPos -= 1; //further left, lower y pos (so it falls sooner)
	}
	yPos = -rightSpawnCount;
	for (int i = 0; i < rightSpawnCount; i++) {
		float xPos = float(rightStart + i * 5 + 1); //+1 to avoid spawning at 0
		createProjectile(xPos, 0);
		yPos += 1;
	}
}

bool ProjectileManager::getSpawing() const 
{
	return spawning;
}

void ProjectileManager::setSpawing(bool b) 
{
	if (b) {
		safeZone->start();
	}
	spawning = b;
}

SafeZone* ProjectileManager::getSafeZone() const
{
	return safeZone;
}