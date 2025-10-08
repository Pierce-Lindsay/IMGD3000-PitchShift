#pragma once
#include "projectile.h"
#include "../engine/game/Object.h"
#include "SafeZone.h"
#include "../engine/Clock.h"

/// <summary>
/// Handles spawning projectiles outside the safe zone once music has started playing and gameplay has started.
/// </summary>
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

	/// <summary>
	/// Get pointer to the safe zone.
	/// </summary>
	SafeZone* getSafeZone() const;

private:
	int draw() override; //not drawable
	int eventHandler(const df::Event* p_event) override;
	bool spawning = false;
	const float SPAWN_INTERVAL = 958.33f; //miliseconds //aligned with beat
	bool initial_offset = true; // is this the first spawn with initial offset?
	bool spawned_arrows = false; //only once per projectile spawn
	const float INITIAL_OFFSET = 0.0f; //first spawn after 100ms
	float lastSpawnTime = 0; //last time we spawned.
	SafeZone* safeZone = nullptr;

};