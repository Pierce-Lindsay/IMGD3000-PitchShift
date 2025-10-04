#include "TestObject.h"
#include <stdexcept>
#include "../engine/game/GameManager.h"
#include "../engine/game/WorldManager.h"
#include "../engine/LogManager.h"
#include "../engine/graphics/DisplayManager.h"
#include "../engine/graphics/Color.h"
#include "../engine/game/EventStep.h"
#include "TestDrawingObject.h"
#include <thread>
#include <iostream>

TestObject::TestObject()
{
	setType("TestObject");
}
int TestObject::eventHandler(const df::Event* p_e)
{
	if (p_e->getType() == df::STEP_EVENT)
	{
		test_step_count = dynamic_cast<const df::EventStep*>(p_e)->getStepCount();
		onFrameTest(); //update each frame
		return 1;
	}
	return 0;
}

void TestObject::onFrameTest()
{
	if (test_step_count == -1)
	{
		std::cout << "TestObject::onFrameTest::Game Engine is stepping wrong, threw error!" << '\n';
		LM.writeLog("TestObject::onFrameTest::Game Engine is stepping wrong, threw error!");
		throw std::runtime_error::exception("Game Engine is stepping wrong!");
	}
	else if (test_step_count >= test_length)
	{
		std::cout << "TestObject::onFrameTest::Game Engine is done!" << '\n';
		//close everything
		LM.writeLog("TestObject::onFrameTest::Game Engine is done!");
		GM.setGameOver(true);
		return;
	}
	int frameAvg = 30; //how many frames to average

	if (test_step_count == 0) //skip first
	{
		clock.delta();
		std::cout << "TestObject::onFrameTest::Integrated test display. On console for real time display. \n If you want to see all test outputs, check the log file." << '\n';
		std::cout << "TestObject::onFrameTest::Lets add some objects, adding 3" << '\n';
		LM.writeLog("TestObject::onFrameTest::Lets add some objects, adding 3");
		//o1 = new TestDrawingObject;
		o1->setPosition(df::Vector(10, 10));
		//o2 = new TestDrawingObject;
		o2->setPosition(df::Vector(20, 20));
		//o3 = new TestDrawingObject;
		o3->setPosition(df::Vector(5,15));
		o3->setVelocity(df::Vector(0, 0.01));

		df::ObjectList objs = WM.objectsOfType("TestDrawingObject");

		for (int i = 0; i < objs.getCount(); i++)
		{
			std::cout << "TestObject::onFrameTest::object " << i << " pos: " << objs[i]->getPosition().x << ", " << objs[i]->getPosition().y << '\n';
			LM.writeLog("TestObject::onFrameTest::object %d pos: %f, %f", i, objs[i]->getPosition().x, objs[i]->getPosition().y);
		}	
	}
	else if(test_step_count % frameAvg == 0)
	{
		long long frameChunk = clock.delta();
		long long avg = frameChunk / (frameAvg * 1000); //in microseconds need miliseconds
		//get frame time from this objects perspective
		std::cout << "TestObject::onFrameTest::From this object's perspective the average frame time has been " << avg << " miliseconds!" << '\n';
		LM.writeLog("TestObject::onFrameTest::From this object's perspective the average frame time has been %lld miliseconds!", avg);
	}

	if (test_step_count == 120) //try inflicting lag
	{
		std::cout << "TestObject::onFrameTest::Lets try to lag it to a 0.5 second frame!" << '\n';
		LM.writeLog("TestObject::onFrameTest::Lets try to lag it to a 0.5 second frame!");
		clock2.delta(); //start a clock to specifically measure th lag delta
		std::this_thread::sleep_for(std::chrono::milliseconds(500)); 
	}

	if (test_step_count == 121) //try inflicting lag
	{
		long long delta = clock2.delta()/1000; //to miliseconds
		std::cout << "TestObject::onFrameTest::This is the frame after the 'lag', it took " << delta << " miliseconds!" << '\n';
		LM.writeLog("TestObject::onFrameTest::This is the frame after the 'lag', it took %lld miliseconds!", delta);	
	}


	if (test_step_count == 160)
	{
		std::cout << "TestObject::onFrameTest::Moving objects by 20!" << '\n';
		LM.writeLog("TestObject::onFrameTest::Moving objects by 20!");
		o1->setPosition(o1->getPosition() + 3);
		o2->setPosition(o2->getPosition() + 3);
		o3->setPosition(o3->getPosition() + 3);

		df::ObjectList objs = WM.objectsOfType("TestDrawingObject");

		for (int i = 0; i < objs.getCount(); i++)
		{
			std::cout << "TestObject::onFrameTest::object " << i << " pos: " << objs[i]->getPosition().x << ", " << objs[i]->getPosition().y << '\n';
			LM.writeLog("TestObject::onFrameTest::object %d pos: %f, %f", i, objs[i]->getPosition().x, objs[i]->getPosition().y);
		}
	}

	if (test_step_count == 210)
	{
		std::cout << "TestObject::onFrameTest::Removing object 2 this frame" << '\n';
		LM.writeLog("TestObject::onFrameTest::Removing object 2 this frame");
		WM.markForDelete(o2);
		o2 = NULL;
	}

	if (test_step_count == 211)
	{
		int count = WM.objectsOfType("TestDrawingObject").getCount();
		std::cout << "TestObject::onFrameTest::Frame after object removal, base object count: " << count << '\n';
		LM.writeLog("TestObject::onFrameTest::Frame after object removal, base object count %d", count);
	}
}