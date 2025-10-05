#include "ProjectileManager.h"
#include "../engine/game/WorldManager.h"
#include "../engine/graphics/DisplayManager.h"
#include "../engine/LogManager.h"
#include "../engine/game/EventStep.h"


ProjectileManager::ProjectileManager() {
	setType("ProjectileManager");
	setSolidness(df::Solidness::SPECTRAL);
}
ProjectileManager::~ProjectileManager() {}

int ProjectileManager::draw() {
	return 0; //not drawable
}

int ProjectileManager::eventHandler(const df::Event* p_event) {
	if (p_event->getType() == df::STEP_EVENT) {
		const df::EventStep* p_step = dynamic_cast<const df::EventStep*>(p_event);
		if (p_step->getStepCount() == 30) //start spawing after 30 steps
			spawing = true;
		if(p_step->getStepCount() % 15 == 0 && spawing) //every 15 steps
			createProjectile();
		return 1;
	}
	return 0;
}

void ProjectileManager::createProjectile() {
	float x_pos = (float)(rand() % DM.getHorizontalChars());
	float speed = (1); //1-3
	df::Color color;
	std::string sprite_label = "projectile1";
	int color_roll = rand() % 3;
	int sprite_roll = rand() % 2;
	if(color_roll == 0)
		color = df::RED;
	else if(color_roll == 1)
		color = df::GREEN;
	else
		color = df::BLUE;

	if(sprite_roll == 1)
		sprite_label = "projectile2";

	Projectile* p = new Projectile(x_pos, color, speed, sprite_label);
	if (p == NULL) {
		LM.writeLog("ProjectileManager::createProjectile: Warning! Could not create projectile");
		return;
	}
	//LM.writeLog("ProjectileManager::createProjectile: Created projectile %d at x: %f, speed: %f", p->getID(), x_pos, speed);
}

bool ProjectileManager::getSpawing() const 
{
	return spawing;
}

void ProjectileManager::setSpawing(bool b) 
{
	spawing = b;
}