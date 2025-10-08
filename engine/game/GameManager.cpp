#include "GameManager.h"
#include "../LogManager.h"
#include "WorldManager.h"
#include "../graphics/DisplayManager.h"
#include "../input/InputManager.h"
#include "../ResourceManager.h"
#include "EventStep.h"
#include <thread>
#include <iostream>

using namespace df;

GameManager::GameManager()
{
	setType("GameManager");
}

GameManager::~GameManager()
{
}

GameManager& GameManager::GetInstance()
{
	static GameManager gm;
	return gm;
}


int GameManager::startUp() 
{
	if (!LM.isStarted())
	{
		if (LM.startUp() == -1)
			return -1;
	}

	if (!DM.isStarted())
	{
		if (DM.startUp() == -1)
			return -1;
	}

	if (!IM.isStarted())
	{
		if (IM.startUp() == -1)
			return -1;
	}

	if (!RM.isStarted())
	{
		if (RM.startUp() == -1)
			return -1;
	}


	if (!WM.isStarted())
	{
		if (WM.startUp() == -1)
			return -1;
	}

	LM.writeLog("GameManager::startUp::Started GameManager Successfully!");

	return Manager::startUp();
}

void GameManager::shutDown() 
{
	WM.shutDown();
	IM.shutDown();
	DM.shutDown();
	RM.shutDown();
	LM.writeLog("GameManager::shutDown::shutdown GameManager Successfully!");
	LM.shutDown(); //close close manager when game manager is shutdown
	Manager::shutDown();
}

void GameManager::run()
{
	if (!isStarted())
		throw std::runtime_error::exception("Can't run game when game manager isn't started!");

	LM.writeLog("GameManager::run:GameManager is now running!");
	EventStep steps;
	Clock ck2;

	while (!game_over)
	{
		frameClock.delta();
		//ck2.delta();
		//inputs

		//update world
		//send step event
		onEvent(&steps);

		//std::cout <<"Frame: " <<steps.getStepCount() << " step 1 miliseconds: " << ck2.delta() / 1000.0f << '\n';

		IM.getInput();

		//std::cout << "Frame: " << "step input miliseconds: " << ck2.delta()/1000.0f << '\n';

		WM.update();

		ck2.delta();

		//render

		WM.draw();

		//std::cout << "Frame: " << "step draw miliseconds: " << ck2.delta() / 1000.0f << '\n';

		//clear buffers and render frame
		DM.swapBuffers();

		//frame rate control
		long long loop_time = frameClock.split();
		//auto actualTimeDiff = (target_time * 1000 - loop_time);
		//auto differance = actualTimeDiff - sleep_correction; //clock in micro-> frames in mili

		if (loop_time> target_time * 1000)
		{
			LM.writeLog("GameManager::run:Running slower that target fps of: %f, actual fps was %f", convertToFPS(target_time * 1000), convertToFPS(loop_time));
		}
		else if (loop_time < target_time * 1000)
		{
			while(loop_time < (target_time * 1000)* 0.99)
			{
				loop_time = frameClock.split();
			}
		}
		delta_time = loop_time / 1000; //in miliseconds


		//if (steps.getStepCount() % 20 == 0)
		//{
			//LM.writeLog("GameManager::run:Fps: %f!", 1.0f / (frameClock.split() / 1000000.0f));
			//std::cout << "GameManager::run:Fps: " << 1.0f / (delta_time/1000.0f) << '\n';
		//}
			

		//step has passed, increment
		steps.setStepCount(steps.getStepCount() + 1);
	}

	LM.writeLog("GameManager::run:GameManager has finished running!");
}

void GameManager::setGameOver(bool game_over)
{
	if (!isStarted())
		throw std::runtime_error::exception("Can't set game over when game manager isn't started!");
	this->game_over = game_over;
}

/// <summary>
/// Gets the current game over status.
/// </summary>
bool GameManager::getGameOver() const
{
	return game_over;
}

int GameManager::getFrameTime() const
{
	return target_time;
}

double GameManager::convertToFPS(int frame_Length)
{
	double d = 1 / (double)(frame_Length);
	d *= 1000000;//in microseconds need seconds
	return d;
}

long long GameManager::getDeltaTime() const
{
	return delta_time;
}

