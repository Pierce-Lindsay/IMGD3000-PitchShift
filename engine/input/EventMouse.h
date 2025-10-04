#pragma once
#include "../Event.h"
#include "../Vector.h"

namespace df 
{
	const std::string MSE_EVENT = "mouse";

	//recognized mouse actions
	enum class EventMouseAction
	{
		UNDEFINED_MOUSE_ACTION = -1,
		CLICKED,
		MOVED,
		ACTION_COUNT, // setinal for valid values
	};

	//recognized mouse buttons
	namespace Mouse {
		enum class Button
		{
			UNDEFINED_MOUSE_BUTTON = -1,
			LEFT,
			RIGHT,
			MIDDLE,
			BUTTON_COUNT, // setinal for valid values
		};
	}

	class EventMouse : public Event
	{
	private:
		EventMouseAction m_mouse_action = EventMouseAction::UNDEFINED_MOUSE_ACTION; //mouse action
		Mouse::Button m_mouse_button = Mouse::Button::UNDEFINED_MOUSE_BUTTON; // mouse button
		Vector m_mouse_pos; // mouse screen pos
	public:
		/// <summary>
		/// Create a new default mouse event;
		/// </summary>
		EventMouse();

		/// <summary>
		/// Set the mouse action for the event.
		/// </summary>
		void setMouseAction(EventMouseAction action);

		/// <summary>
		/// Get the mouse action for the event.
		/// </summary>
		EventMouseAction getMouseAction() const;

		/// <summary>
		/// Set the mouse button for the event.
		/// </summary>
		void setMouseButton(Mouse::Button button);

		/// <summary>
		/// Get the mouse button for the event.
		/// </summary>
		Mouse::Button getMouseButton() const;

		/// <summary>
		/// Set the mouse position for the event.
		/// </summary>
		void setMousePosition(Vector pos);

		/// <summary>
		/// Get the mouse position for the event.
		/// </summary>
		Vector getMousePosition() const;
	};

}