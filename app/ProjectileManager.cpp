#include "ProjectileManager.h"
#include "../engine/game/WorldManager.h"
#include "../engine/graphics/DisplayManager.h"
#include "../engine/LogManager.h"
#include "../engine/game/EventStep.h"
#include "../engine/Utility.h"
#include "../engine/graphics/Color.h"
#include "../engine/game/GameManager.h"
#include <array>

std::array<std::string, 2> sprite_labels = {"projectile2" }; //potential sprites for projectiles


ProjectileManager::ProjectileManager(SafeZone* safeZone) {
	setType("ProjectileManager");
	setSolidness(df::Solidness::SPECTRAL);
	this->safeZone = safeZone;
}
ProjectileManager::~ProjectileManager() {}

int ProjectileManager::draw() {
	return 0; //not drawable
}

int ProjectileManager::eventHandler(const df::Event* p_event) {
	if(safeZone == nullptr) {
		LM.writeLog("ProjectileManager::eventHandler: Warning! No safe zone provided, cannot spawn projectiles.");
		return 0;
	}
	if (p_event->getType() == df::STEP_EVENT) {
		const df::EventStep* p_step = dynamic_cast<const df::EventStep*>(p_event);
		if (p_step->getStepCount() == 30) //start spawing after 30 steps
		{
			spawning = true;
			safeZone->start();
		}
		float curTime = 0;
		if (safeZone->hasStarted() && (curTime = safeZone->getMusicTime()) - lastSpawnTime >= SPAWN_INTERVAL && spawning) //every 1/2 second
		{
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
	float speed = 1;
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

	LM.writeLog("ProjectileManager::createProjectiles::Safe zone pos: %f", safeZoneCenter);

	int leftEnd = safeZoneCenter - (safeZone->getWidth() / 2); //0 - left end of safe zone
	int rightStart = safeZoneCenter + (safeZone->getWidth() / 2); //right end of safe zone - max screen width
	int rightEnd = DM.getHorizontalChars();

	//spawn 1 projectile per ever other char position, avoiding the safe zone
	if (leftEnd < 0) leftEnd = 0;
	if (rightStart > DM.getHorizontalChars()) rightStart = DM.getHorizontalChars();

	int leftSpawnCount = leftEnd / 5; //every other position
	int rightSpawnCount = (rightEnd - rightStart) / 5; //every other position

	//we want spikes to drop sooner when further away from safe zone
	float yPos = 0;
	for (int i = 0; i < leftSpawnCount; i++) {
		float xPos = float(i * 5 + 1); //+1 to avoid spawning at 0
		createProjectile(xPos, yPos);
		yPos -= 1; //further left, lower y pos (so it falls sooner)
	}
	yPos = -rightSpawnCount;
	for (int i = 0; i < rightSpawnCount; i++) {
		float xPos = float(rightStart + i * 5 + 1); //+1 to avoid spawning at 0
		createProjectile(xPos, yPos);
		yPos += 1;
	}
}

bool ProjectileManager::getSpawing() const 
{
	return spawning;
}

void ProjectileManager::setSpawing(bool b) 
{
	spawning = b;
}