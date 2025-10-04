#pragma once
#include "../Event.h"

namespace df {
	const std::string KEYBOARD_EVENT = "keyboard";

	// accpedted keyboard actions
	enum class EventKeyboardAction
	{
		UNDEFINED_KEYBOARD_ACTION = -1,
		 KEY_PRESSED, // down
		 KEY_RELEASED, // released	
		 ACTION_COUNT, // setinal for valid values
	};
	namespace Keyboard {
		// recognized keys //note I added all the SFML supported keys in the same order
		enum class Key
		{
			UNDEFINED_KEY = -1, A = 0,
			B, C,
			D, E, F, G,
			H, I, J, K,
			L, M, N, O,
			P, Q, R, S,
			T, U, V, W,
			X, Y, Z, NUM0,
			NUM1, NUM2, NUM3, NUM4,
			NUM5, NUM6, NUM7, NUM8,
			NUM9, ESCAPE, LCONTROL, LSHIFT,
			LALT, LSYSTEM, RCONTROL, RSHIFT,
			RALT, RSYSTEM, MENU, LBRACKET,
			RBRACKET, SEMICOLON, COMMA, PERIOD,
			APOSTROPHE, SLASH, BACKSLASH, GRAVE,
			EQUAL, HYPHEN, SPACE, ENTER,
			BACKSPACE, TAB, PAGEUP, PAGEDOWN,
			END, HOME, INSERT, DELETE,
			ADD, SUBTRACT, MULTIPLY, DIVIDE,
			LEFT, RIGHT, UP, DOWN,
			NUMPAD0, NUMPAD1, NUMPAD2, NUMPAD3,
			NUMPAD4, NUMPAD5, NUMPAD6, NUMPAD7,
			NUMPAD8, NUMPAD9, F1, F2,
			F3, F4, F5, F6,
			F7, F8, F9, F10,
			F11, F12, F13, F14,
			F15, PAUSE, KEYCOUNT, TILDE = GRAVE,
			DASH = HYPHEN, RETURN = ENTER, QUOTE = APOSTROPHE
		};
	}

	class EventKeyboard : public Event {

	private:
		Keyboard::Key m_key_val = Keyboard::Key::UNDEFINED_KEY; // key value
		EventKeyboardAction m_keyboard_action = EventKeyboardAction::UNDEFINED_KEYBOARD_ACTION; // key action

	public:
		/// <summary>
		/// Create a new keyboard event.
		/// </summary>
		EventKeyboard();

		/// <summary>
		/// Set the value of this events key.
		/// </summary>
		void setKey(Keyboard::Key new_key);

		/// <summary>
		/// Get the value of this events key.
		/// </summary>
		Keyboard::Key getKey() const;

		/// <summary>
		/// Set the value of this events key action.
		/// </summary>
		void setKeyboardAction(EventKeyboardAction new_action);

		/// <summary>
		/// get the value of this events key action.
		/// </summary>
		EventKeyboardAction getKeyboardAction() const;
	};
}