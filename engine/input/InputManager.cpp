#include "InputManager.h"
#include "../graphics/DisplayManager.h"
#include "../LogManager.h"
#include "EventKeyboard.h"
#include "EventMouse.h"
#include "../game/WorldManager.h"
#include"../game/GameManager.h"
using namespace df;

InputManager::InputManager()
{
	setType("InputManager");
}

InputManager::~InputManager()
{

}

InputManager& InputManager::GetInstance()
{
	static InputManager im;
	return im;
}

int InputManager::startUp()
{
	//needs lm for logging, if isn't started, start it
	if (!LM.isStarted())
	{
		if (LM.startUp() == -1)
			return -1;
	}

	if (!DM.isStarted())
	{
		LM.writeLog("InputManager::startUp::Failed to start up, DisplayManager must be started before the InputManager.");
		return -1;
	}

	//disable key repeats
	auto window = DM.getWindow();
	window->setKeyRepeatEnabled(false);

	LM.writeLog("InputManager::startUp::Successfully started the InputManager.");
	return Manager::startUp();
}

void InputManager::shutDown()
{
	LM.writeLog("InputManager::shutDown::Successfully shutdown the InputManager.");
	Manager::shutDown();
}

void InputManager::getInput() const
{
	// See if window has been closed.
	while (const std::optional<sf::Event> win_event = DM.getWindow()->pollEvent()) {
		if (!win_event.has_value()) //leave if no values
			return; //no inputs, just leave
		sf::Event e = win_event.value();

		if (win_event->is<sf::Event::Closed>())
		{
			if (GM.isStarted()) // close the game if window is closed
				GM.setGameOver(true);
			return; //don't need any more inputs
		}
		else if (win_event->is<sf::Event::KeyPressed>())
		{
			sf::Event::KeyPressed* event = reinterpret_cast<sf::Event::KeyPressed*>(&e);
			EventKeyboard df_key_event;
			df_key_event.setKey(convertSFKeyCodeToDF(event->code));
			df_key_event.setKeyboardAction(df::EventKeyboardAction::KEY_PRESSED);
			WM.onEvent(&df_key_event);
		}
		else if (win_event->is<sf::Event::KeyReleased>())
		{
			sf::Event::KeyReleased* event = reinterpret_cast<sf::Event::KeyReleased*>(&e);
			EventKeyboard df_key_event;
			df_key_event.setKey(convertSFKeyCodeToDF(event->code));
			df_key_event.setKeyboardAction(df::EventKeyboardAction::KEY_RELEASED);
			WM.onEvent(&df_key_event);
		}
		else if (win_event->is < sf::Event::MouseButtonPressed>())
		{
			sf::Event::MouseButtonPressed* event = reinterpret_cast<sf::Event::MouseButtonPressed*>(&e);
			EventMouse df_mouse_event;
			auto event_pos = event->position;
			df_mouse_event.setMouseButton(convertSFMouseButtonCodeToDF(event->button));
			df_mouse_event.setMouseAction(df::EventMouseAction::CLICKED);
			df_mouse_event.setMousePosition(Vector(event_pos.x, event_pos.y));
			WM.onEvent(&df_mouse_event);
		}
		else if (win_event->is < sf::Event::MouseMoved>())
		{
			sf::Event::MouseMoved* event = reinterpret_cast<sf::Event::MouseMoved*>(&e);
			EventMouse df_mouse_event;
			auto event_pos = event->position;
			df_mouse_event.setMousePosition(Vector(event_pos.x, event_pos.y));
			WM.onEvent(&df_mouse_event);
		}
	}
}

Keyboard::Key InputManager::convertSFKeyCodeToDF(sf::Keyboard::Key sf_key) const
{ //only convert if safe keycodes are all the same to make this conversion super easy
	if (static_cast<int>(sf_key) >= static_cast<int>(df::Keyboard::Key::KEYCOUNT))
		return df::Keyboard::Key::UNDEFINED_KEY;
	return static_cast<df::Keyboard::Key>(static_cast<int>(sf_key));

}

Mouse::Button InputManager::convertSFMouseButtonCodeToDF(sf::Mouse::Button sf_mouse) const
{
	switch (sf_mouse)
	{
	case sf::Mouse::Button::Left:
		return df::Mouse::Button::LEFT;
	case sf::Mouse::Button::Right:
		return df::Mouse::Button::RIGHT;
	case sf::Mouse::Button::Middle:
		return df::Mouse::Button::MIDDLE;
	default:
		df::Mouse::Button::UNDEFINED_MOUSE_BUTTON;
	}
}