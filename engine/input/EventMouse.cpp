#include "EventMouse.h"
#include "../LogManager.h"
using namespace df;

EventMouse::EventMouse() : m_mouse_pos(0, 0)
{
	setType(MSE_EVENT);
}

void EventMouse::setMouseAction(EventMouseAction action)
{
	int new_val = static_cast<int>(action);
	if (new_val >= static_cast<int>(EventMouseAction::ACTION_COUNT) || new_val < -1)
	{
		LM.writeLog("EventMouse::setMouseAction::Tried to assign unknown code of: %d", new_val);
		m_mouse_action = EventMouseAction::UNDEFINED_MOUSE_ACTION;
	}
	else
		m_mouse_action = action;
}

EventMouseAction EventMouse::getMouseAction() const
{
	return m_mouse_action;
}

void EventMouse::setMouseButton(Mouse::Button button)
{
	int new_val = static_cast<int>(button);
	if (new_val >= static_cast<int>(Mouse::Button::BUTTON_COUNT) || new_val < -1)
	{
		LM.writeLog("EventMouse::setMouseButton::Tried to assign unknown code of: %d", new_val);
		m_mouse_button = Mouse::Button::UNDEFINED_MOUSE_BUTTON;
	}
	else
		m_mouse_button = button;
}

Mouse::Button EventMouse::getMouseButton() const
{
	return m_mouse_button;
}

void EventMouse::setMousePosition(Vector pos)
{
	m_mouse_pos = pos;
}

Vector EventMouse::getMousePosition() const
{
	return m_mouse_pos;
}