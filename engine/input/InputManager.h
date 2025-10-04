#pragma once
#include "../Manager.h"
#include "SFML/Window/Event.hpp"
#include "SFML/Window/Keyboard.hpp"
#include "SFML/Window/Mouse.hpp"
#include "EventKeyboard.h"
#include "EventMouse.h"

#define IM df::InputManager::GetInstance()

namespace df {
	/// <summary>
	/// A class for managing external inputs into the game engine.
	/// </summary>
	class InputManager : public Manager
	{
	private:
		//singleton stuff
		InputManager();
		InputManager(InputManager const& copy);
		void operator=(InputManager const& assign);

		/// <summary>
		/// Converts a given SFML keycode to the respective dragonfly keycode or undefined if
		/// dragonfly lacks the keycode.
		/// </summary>
		/// <returns>A Dragnfly key code.</returns>
		df::Keyboard::Key convertSFKeyCodeToDF(sf::Keyboard::Key) const;

		/// <summary>
		/// Converts a given SFML mouse button code to the respective dragonfly button code or undefined if
		/// dragonfly lacks the mouse button code.
		/// </summary>
		/// <returns>A Dragnfly mouse button code.</returns>
		df::Mouse::Button convertSFMouseButtonCodeToDF(sf::Mouse::Button sf_mouse) const;


	public:
		/// <summary>
		/// Destroys the input manager and any other dependencies.
		/// </summary>
		~InputManager();

		/// <summary>
		/// Get instance of the one and only InputManager.
		/// </summary>
		/// <returns></returns>
		static InputManager& GetInstance();

		/// <summary>
		/// Start up InputManager and required dependencies.
		/// </summary>
		/// <returns>0 if successful.</returns>
		int startUp() override;

		/// <summary>
		/// Shut down InputManager and required dependencies. 
		/// </summary>
		void shutDown() override;


		/// <summary>
		/// Passes a given input event from keyboard/mouse to all objects.
		/// </summary>
		void getInput() const;
	};
}