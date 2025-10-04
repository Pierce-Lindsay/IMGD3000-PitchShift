#include "TestPlayer.h"

#include <stdexcept>
#include "../engine/game/GameManager.h"
#include "../engine/input/EventKeyboard.h"
#include "../engine/input/EventMouse.h"
#include "../engine/game/WorldManager.h"
#include "../engine/LogManager.h"
#include "../engine/graphics/DisplayManager.h"
#include "../engine/ResourceManager.h"
#include "../engine/game/EventCollision.h"
#include "../engine/game/EventStep.h"
#include "../engine/Utility.h"
#include "../engine/graphics/Color.h"
#include "../engine/box.h"
#include "SpriteObject.h"
#include "TestDrawingObject.h"
#include <thread>
#include <iostream>

TestPlayer::TestPlayer()
{
	setType("TestPlayer");
	setPosition(df::Vector(40, 19));
	reticle = new TestDrawingObject("+");
	reticle->setSolidness(df::Solidness::SPECTRAL);
	reticle->setAltitude(df::MAX_ALTITUDE);

	df::Vector pos12(20, 15);
	startGameText = new TestDrawingObject("Press spacebar to begain collision test game!");
	startGameText->setSolidness(df::Solidness::SPECTRAL);
	startGameText->setPosition(pos12);
	//start music

	start_music = RM.getMusic("music1");
	start_music->play(true);	
}
int TestPlayer::eventHandler(const df::Event* p_e)
{
	df::Vector new_v(0, 0);
	//test a whole bunch of different inputs and create different interactions based on them
	if (p_e->getType() == df::COLLISION_EVENT)
	{
		df::Vector p1(20, 10);
		TestDrawingObject* t1 = new TestDrawingObject("Collided!");
		t1->setColor(df::RED);
		t1->setPosition(p1);
		t1->setVelocity(df::Vector(0, -1));
		t1->setSolidness(df::Solidness::SPECTRAL);
	}
	else if (p_e->getType() == df::MSE_EVENT)
	{
		const df::EventMouse* me = dynamic_cast<const df::EventMouse*>(p_e);
		reticle->setPosition(pixelsToSpaces(me->getMousePosition()));

		if (me->getMouseAction() == df::EventMouseAction::CLICKED &&
			me->getMouseButton() == df::Mouse::Button::LEFT)
		{
			//spawn object with down velocity
			TestDrawingObject* t = new TestDrawingObject("5");
			t->setPosition(getPosition());
			df::Vector dir = (df::Vector(0, 1));
			t->setSolidness(df::Solidness::SPECTRAL);
			t->setDirection(dir);
			t->setSpeed(2);
			t->setColor(df::RED);
			RM.getSound("fire")->play();
		}
	}
	else if (p_e->getType() == df::KEYBOARD_EVENT)
	{
		const df::EventKeyboard* kb = dynamic_cast<const df::EventKeyboard*>(p_e);

		bool down = kb->getKeyboardAction() == df::EventKeyboardAction::KEY_PRESSED;
		bool release = kb->getKeyboardAction() == df::EventKeyboardAction::KEY_RELEASED;

		if (!collisionTestStarted && kb->getKey() == df::Keyboard::Key::SPACE && down)
		{
			start_music->stop();
			collisionTestStarted = true;
			WM.markForDelete(startGameText);
			//spawn new objects
			df::Vector p1(15, 20);
			SpriteObject* t1 = new SpriteObject("laser");
			t1->setPosition(p1);
			t1->setSolidness(df::Solidness::SPECTRAL);

			df::Vector p1name(10, 14);
			TestDrawingObject* t1name = new TestDrawingObject("Spectral");
			t1name->setPosition(p1name);
			t1name->setColor(df::PURPLE);

			//spawn new objects
			df::Vector p2(30, 20);
			SpriteObject* t2 = new SpriteObject("powerup");
			t2->setPosition(p2);
			t2->setSolidness(df::Solidness::SOFT);

			df::Vector p2name(28, 14);
			TestDrawingObject* t2name = new TestDrawingObject("Soft");
			t2name->setPosition(p2name);
			t2name->setColor(df::PURPLE);

			//spawn new objects
			df::Vector p3(45, 20);
			SpriteObject* t3 = new SpriteObject("chunk");
			t3->setPosition(p3);
			t3->setSolidness(df::Solidness::HARD);

			df::Vector p3name(44, 14);
			TestDrawingObject* t3name = new TestDrawingObject("Hard");
			t3name->setPosition(p3name);
			t3name->setColor(df::PURPLE);

			//spawn new objects
			df::Vector pfrazzle(60, 20);
			SpriteObject* tfrazzle = new SpriteObject("frazzle");
			tfrazzle->setPosition(pfrazzle);
			tfrazzle->setSolidness(df::Solidness::SPECTRAL);

			df::Vector fnamepos(52, 16);
			TestDrawingObject* fname = new TestDrawingObject("Long Animation");
			fname->setPosition(fnamepos);
			fname->setColor(df::PURPLE);

			df::Vector p4name(20, 11);
			TestDrawingObject* t4name = new TestDrawingObject("Fire with left mouse click");
			t4name->setPosition(p4name);
			t4name->setColor(df::GREEN);

			df::Vector p5name(20, 10);
			TestDrawingObject* t5name = new TestDrawingObject("Move with w,a,s,d, try to collide!");
			t5name->setPosition(p5name);
			t5name->setColor(df::GREEN);

			df::Vector p6name(20, 9);
			TestDrawingObject* t6name = new TestDrawingObject("Press escape to end game/test!");
			t6name->setPosition(p6name);
			t6name->setColor(df::RED);

			df::Vector p7name(30, 7.5);
			TestDrawingObject* t7name = new TestDrawingObject("Collision boxes shown by red dashes on 'solids'");
			t7name->setPosition(p7name);
			t7name->setColor(df::YELLOW);
		}

		if (kb->getKey() == df::Keyboard::Key::W && down)
		{
			new_v.y -= 0.25;
		}

		if (kb->getKey() == df::Keyboard::Key::S && down)
		{
			new_v.y += 0.25;
		}

		if (kb->getKey() == df::Keyboard::Key::A && down)
		{
			new_v.x -= 0.25;
		}

		if (kb->getKey() == df::Keyboard::Key::D && down)
		{
			new_v.x += 0.25;
		}
		setVelocity(new_v);


		if (kb->getKey() == df::Keyboard::Key::ESCAPE && down)
			GM.setGameOver(true); //end game
	}
	else if (p_e->getType() == df::STEP_EVENT)
	{
		//create hitbox borders
		auto objects = WM.getAllObjects();
		for (int i = 0; i < objects.getCount(); i++)
		{
			if (objects[i]->isSolid())
			{
				df::Box hb = df::getWorldBox(objects[i]);
				df::Vector tl = hb.getCorner();
				df::Vector tr(tl.x + hb.getHorizontal(), tl.y);
				df::Vector br(tl.x + hb.getHorizontal(), tl.y + hb.getVertical());
				df::Vector bl(tl.x, tl.y + hb.getVertical());
				//draw hit box
				DM.drawCh(tl, '-', df::RED);
				DM.drawCh(tr, '-', df::RED);
				DM.drawCh(bl, '-', df::RED);
				DM.drawCh(br, '-', df::RED);
			}
		}

	}
	return 0;
}


int TestPlayer::draw()
{
	return DM.drawCh(getPosition(), 'P', df::TURQUOISE);
}