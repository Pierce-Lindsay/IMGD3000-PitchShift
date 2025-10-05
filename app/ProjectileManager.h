#pragma once
#include "projectile.h"
#include "../engine/game/Object.h"

class ProjectileManager : public df::Object {
public:
	ProjectileManager();
	/// <summary>
	/// Creates a projectile in a position according to...
	/// </summary>
	void createProjectile();

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
};