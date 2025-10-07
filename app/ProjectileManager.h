#pragma once
#include "projectile.h"
#include "../engine/game/Object.h"
#include "SafeZone.h"
#include "../engine/Clock.h"

class ProjectileManager : public df::Object {
public:
	ProjectileManager(SafeZone* safeZone);

	~ProjectileManager();
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


	SafeZone* getSafeZone() const;

private:
	int draw() override; //not drawable
	int eventHandler(const df::Event* p_event) override;
	bool spawning = false;
	const float SPAWN_INTERVAL = 1000.0f; //miliseconds
	bool initial_offset = true;
	const float INITIAL_OFFSET = 100.0f; //first spawn after 100ms
	float lastSpawnTime = 0;
	SafeZone* safeZone = nullptr;

};