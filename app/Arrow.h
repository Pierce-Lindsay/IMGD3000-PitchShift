#pragma once
#include "../engine/game/Object.h"

/// <summary>
/// An arrow that spawns in and moves left or right given boolean from position.
/// </summary>
class Arrow : public df::Object
{
public:
	Arrow(bool right, df::Vector pos);

	int eventHandler(const df::Event* p_e) override;
};