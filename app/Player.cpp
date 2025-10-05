#include "Player.h"

#include "../engine/LogManager.h"
#include "../engine/game/WorldManager.h"
#include "../engine/graphics/DisplayManager.h"
#include "../engine/game/GameManager.h"

#include "../engine/game/EventCollision.h"
#include "../engine/input/EventKeyboard.h"
#include "../engine/game/EventOut.h"
#include "../engine/game/EventStep.h"

Player::Player() {
	setType("Player");
	setSolidness(df::Solidness::HARD);
	setPosition(df::Vector((float)(DM.getHorizontalChars() / 2), (float)(DM.getVerticalChars() - 3)));
	setSprite("player");
	if(getSprite() == NULL) {
		LM.writeLog("Player::Player: Warning! Sprite not found: player");
		return;
	}
	setAltitude(3);
	health = 3;
	score = 0;
	speed = 1.0f;
	dx = 0;
	setSpeed(speed);
}

Player::~Player() {
	GM.setGameOver();
}

int Player::eventHandler(const df::Event* p_e) {
	if (p_e->getType() == df::OUT_EVENT) {
		const df::EventOut* p_out_event = dynamic_cast<const df::EventOut*>(p_e);
		LM.writeLog("Player::eventHandler: Player out of bounds, resetting position");
		setPosition(df::Vector((float)(DM.getHorizontalChars() / 2), (float)(DM.getVerticalChars() - 3)));
		return 1;
	}

	if (p_e->getType() == df::COLLISION_EVENT) {
		//const df::EventCollision* p_collision_event = dynamic_cast<const df::EventCollision*>(p_e);
		//if (p_collision_event->getObject1()->getType() == "Projectile" || p_collision_event->getObject2()->getType() == "Projectile") {
		//	LM.writeLog("Player::eventHandler: Player collision with projectile");
		//	setHealth(health - 1);
		//	if (health <= 0) {
		//		LM.writeLog("Player::eventHandler: Player health zero, game over");
		//		WM.markForDelete(this);
		//	}
		//	return 1;
		//}
		//return 0;
	}

	if (p_e->getType() == df::KEYBOARD_EVENT) {
		const df::EventKeyboard* p_keyboard_event = dynamic_cast<const df::EventKeyboard*>(p_e);
		handleInput(p_keyboard_event);
		return 1;
	}

	if (p_e->getType() == df::STEP_EVENT) {
		step();
		return 1;
	}

	return 0;
}

void Player::setHealth(int new_health) {
	health = new_health;
}

int Player::getHealth() const {
	return health;
}

void Player::setScore(int new_score) {
	score = new_score;
}

int Player::getScore() const {
	return score;
}

void Player::handleInput(const df::EventKeyboard* p_keyboard_event) {
	switch(p_keyboard_event->getKey()) {
		case df::Keyboard::Key::LEFT:
		case df::Keyboard::Key::A:
			if(p_keyboard_event->getKeyboardAction() == df::EventKeyboardAction::KEY_RELEASED)
				dx += 1;
			else if (p_keyboard_event->getKeyboardAction() == df::EventKeyboardAction::KEY_PRESSED)
				dx -= 1;
			break;
		case df::Keyboard::Key::RIGHT:
		case df::Keyboard::Key::D:
			if (p_keyboard_event->getKeyboardAction() == df::EventKeyboardAction::KEY_RELEASED)
				dx -= 1;
			else if (p_keyboard_event->getKeyboardAction() == df::EventKeyboardAction::KEY_PRESSED)
				dx += 1;
			break;
		case df::Keyboard::Key::Q:
			// Kill player and end game
			LM.writeLog("Player::handleInput: Player quit, game over");
			WM.markForDelete(this);
			break;
		default:
			break;
	}
}

void Player::move() {
	if (dx != 0) {
		df::Vector new_pos = getPosition();
		new_pos.x += dx * speed;
		WM.moveObject(this, new_pos);
	}
}

void Player::step() {
	move();
}