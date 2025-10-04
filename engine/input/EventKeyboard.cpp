#include "EventKeyboard.h"
#include "../LogManager.h"

using namespace df;


EventKeyboard::EventKeyboard()
{
	setType(KEYBOARD_EVENT);
}

void EventKeyboard::setKey(Keyboard::Key new_key)
{
	int new_val = static_cast<int>(new_key);
	if (new_val >= static_cast<int>(Keyboard::Key::KEYCOUNT) || new_val < -1)
	{
		LM.writeLog("EventKeyboard::setKey::Tried to assign unknown code of: %d", new_val);
		m_key_val = Keyboard::Key::UNDEFINED_KEY;
	}
	else
		m_key_val = new_key;
}

Keyboard::Key EventKeyboard::getKey() const
{
	return m_key_val;
}


void EventKeyboard::setKeyboardAction(EventKeyboardAction new_action)
{
	int new_val = static_cast<int>(new_action);
	if (new_val >= static_cast<int>(EventKeyboardAction::ACTION_COUNT) || new_val < -1)
	{
		LM.writeLog("EventKeyboard::setKeyboardAction::Tried to assign unknown code of: %d", new_val);
		m_keyboard_action = EventKeyboardAction::UNDEFINED_KEYBOARD_ACTION;
	}
	else
		m_keyboard_action = new_action;
}

EventKeyboardAction EventKeyboard::getKeyboardAction() const
{
	return m_keyboard_action;
}