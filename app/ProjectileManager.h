#pragma once
#include "projectile.h"
#include "../engine/game/Object.h"
#include "SafeZone.h"

class ProjectileManager : public df::Object {
public:
	ProjectileManager(SafeZone* safeZone);
	/// <summary>
	/// Creates a projectile in a position according to...
	/// </summary>
	void createProjectile(float xPos, float yPos);

	/// <summary>
	/// Spawn all neccesary projectiles outside the safe zone.
	/// </summary>
	void createProjectiles();

	/// <summary>
	/// Returns whether spawning is currently active.
	/// </summary>
	bool getSpawing() const;

	/// <summary>
	/// Sets the spawning state.
	/// </summary>
	void setSpawing(bool b);
	
private: 
	int draw() override; //not drawable
	int eventHandler(const df::Event* p_event) override;
	~ProjectileManager();
	bool spawning = false;
	SafeZone* safeZone = nullptr;
};