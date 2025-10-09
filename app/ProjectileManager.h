#pragma once
#include "projectile.h"
#include "../engine/game/Object.h"
#include "SafeZone.h"
#include "../engine/Clock.h"
#include "../engine/graphics/Color.h"
#include <array>

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
	const float SPAWN_INTERVAL = 1000.f; //miliseconds //aligned with beat
	const float SPAWN_SPACING = 4.75f;
	const float Y_BASE_SPAWN_POS = -1;
	const float Y_SPAWN_DELTA = 1.f; //we want projectiles next to teh edges(near portal) to spawn higher
	const float Y_MAX_SPEED_DELTA = 0.05; //this is a fraction of the current speed
	const float BASE_PROJECTILE_SPEED = 0.4;
	const float SPEED_LEVELUP_INCREASE = 0.05;
	const float INITIAL_OFFSET = 0.0f; //first spawn after 100ms
	int current_color_index = 0;
	const std::string SPRITE_LABEL = "projectile2";
	std::array<df::Color, 7> color_array = { df::GREEN, df::TURQUOISE,
		df::Color(100, 100, 255, 255), df::YELLOW, df::ORANGE, df::RED, df::WHITE };

	float projectile_speed = BASE_PROJECTILE_SPEED;

	bool initial_offset = true; // is this the first spawn with initial offset?
	bool spawned_arrows = false; //only once per projectile spawn
	float lastSpawnTime = 0; //last time we spawned.
	SafeZone* safeZone = nullptr;

};