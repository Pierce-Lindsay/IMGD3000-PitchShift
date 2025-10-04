#pragma once
#include "../engine/graphics/Justification.h"
#include "../engine/graphics/Color.h"
#include "../engine/game/Object.h"
#include "../engine/Event.h"
/// <summary>
/// Class for a pretend user object that inherits from object that tests drawing functionalities.
/// A major piece of code that works the integrated test.
/// </summary>
class TestDrawingObject : public df::Object
{
private:
	std::string whatToDraw = " ";
	df::Color color = df::WHITE;
	df::Justification just = df::Justification::RIGHT;

public:
	/// <summary>
	/// Create and set type.
	/// </summary>
	TestDrawingObject(std::string whatToDraw);

	/// <summary>
	/// Handle step event.
	/// </summary>
	int eventHandler(const df::Event* p_e) override;

	/// <summary>
	/// Draw our test rawing object.
	/// </summary>
	int draw() override;

	/// <summary>
	/// Set teh color for drawing.
	/// </summary>
	void setColor(df::Color c);

	/// <summary>
	/// Set the justification for drawing.
	/// </summary>
	void setJust(df::Justification j);
};