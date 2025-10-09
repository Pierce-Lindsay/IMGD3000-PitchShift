#include "Player.h"

#include "../engine/LogManager.h"
#include "../engine/game/WorldManager.h"
#include "../engine/graphics/DisplayManager.h"
#include "../engine/game/GameManager.h"
#include "../engine/game/ObjectList.h"
#include "../engine/graphics/Sprite.h"
#include "../engine/ResourceManager.h"

#include "../engine/game/EventOut.h"
#include "../engine/game/EventStep.h"
#include "EventChangeColor.h"
#include "GameOver.h"
#include "GameStart.h"

Player::Player() {
	setType("Player");
	setSolidness(df::Solidness::HARD);
	setPosition(df::Vector((float)(DM.getHorizontalChars() / 2), (float)(DM.getVerticalChars() - 5)));
	setSprite("player");
	if(getSprite() == NULL) {
		LM.writeLog("Player::Player: Warning! Sprite not found: player");
		return;
	}
	setAltitude(3);
	health = 3;
	score = 0;
	speed = 2.f;
	dx = 0;
	invincibility_timer = 0;
	invincibility_duration = 60; // 60 frames of invincibility
	isHit = false;
	setSpeed(speed);
}

Player::~Player() {
	getSprite()->setColor(df::WHITE); //reset color in case it was changed
	new GameOver;
}

int Player::eventHandler(const df::Event* p_e) {
	if (p_e->getType() == df::OUT_EVENT) {
		const df::EventOut* p_out_event = dynamic_cast<const df::EventOut*>(p_e);
		if (!should_teleport)
		{
			LM.writeLog("Player::eventHandler: Player out of bounds, resetting position");
			setPosition(df::Vector((float)(DM.getHorizontalChars() / 2), (float)(DM.getVerticalChars() - 5)));
		}
		return 1;
	}

	if (p_e->getType() == df::COLLISION_EVENT) {
		const df::EventCollision* p_collision_event = dynamic_cast<const df::EventCollision*>(p_e);
		hit(p_collision_event);
		return 1;
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

	if (p_e->getType() == TELEPORT_EVENT) {
		const EventTeleport* p_teleport_event = dynamic_cast<const EventTeleport*>(p_e);
		teleport(p_teleport_event);
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
		case df::Keyboard::Key::C:
			if (p_keyboard_event->getKeyboardAction() == df::EventKeyboardAction::KEY_PRESSED) {
				setPosition(df::Vector((float)(DM.getHorizontalChars() / 2), (float)(DM.getVerticalChars() - 5)));
			}
			break;
		case df::Keyboard::Key::H:
			if (p_keyboard_event->getKeyboardAction() == df::EventKeyboardAction::KEY_PRESSED) {
				LM.writeLog("Player::handleInput: Player health increased");
				health += 1;
			}
			break;
		case df::Keyboard::Key::X:
			setPosition(df::Vector((float)(DM.getHorizontalChars() - 7), getPosition().y));
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

	if(should_teleport)
	{
		LM.writeLog("Player::step: Teleporting player to (%f, %f)", teleport_position.x, teleport_position.y);
		setPosition(teleport_position);
		should_teleport = false;

		EventChangeColor color_event;
		if(teleport_position.x == TELEPORT_DELTA)
			color_event.setToHigherPitch(false);
		else
			color_event.setToHigherPitch(true);
		WM.onEvent(&color_event);
	}
	move();

	df::Sprite* p_sprite = getSprite();

	if (isHit) {
		invincibility_timer--;

		if (invincibility_timer % 2 != 0) {
			p_sprite->setColor(df::BLACK);
		} else {
			p_sprite->setColor(df::WHITE);
		}

		if (invincibility_timer <= 0) {
			isHit = false;
			invincibility_timer = 0;
		}
	}
}

void Player::hit(const df::EventCollision* p_collision_event) {
	if (p_collision_event->getObject1()->getType() == "Projectile" ||
		p_collision_event->getObject2()->getType() == "Projectile") {
		LM.writeLog("Player::eventHandler: Player hit by projectile");
		if (!isHit) {
			LM.writeLog("Player::eventHandler: Player health decreased");
			health -= 1;
			isHit = true;
			invincibility_timer = invincibility_duration;
			RM.getSound("explode")->play();
			if (health <= 0) {
				LM.writeLog("Player::eventHandler: Player health depleted, game over");
				WM.markForDelete(this);
			}
		}
	}
}

void Player::teleport(const EventTeleport* p_teleport_event) {
	if (p_teleport_event->isToHigherPitch()) {
		LM.writeLog("Player::teleport: Teleporting to higher pitch");
		teleport_position = df::Vector(TELEPORT_DELTA, getPosition().y);
	}
	else {
		LM.writeLog("Player::teleport: Teleporting to lower pitch");
		teleport_position = df::Vector((float)(DM.getHorizontalChars() - TELEPORT_DELTA), getPosition().y);
	}
	should_teleport = true;
	LM.writeLog("Player::teleport: Player position after teleport: (%f, %f)", teleport_position.x, teleport_position.y);
}

void Player::kill() {
	LM.writeLog("Player::kill: Player killed");
	WM.markForDelete(this);
}