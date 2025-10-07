#pragma once
#include "../engine/game/Object.h"
#include "../engine/graphics/Color.h"
#include "EventChangeColor.h"

/// <summary>
/// Floor object, spectral, decoration tat changes color according to the music.
/// </summary>
class Floor : public df::Object {
	public:
		Floor();
		~Floor();
};