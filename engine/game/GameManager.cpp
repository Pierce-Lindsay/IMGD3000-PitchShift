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

	while (!game_over)
	{
		frameClock.delta();
		//inputs

		//update world
		//send step event
		onEvent(&steps);

		IM.getInput();

		WM.update();

		//render

		WM.draw();

		//clear buffers and render frame
		DM.swapBuffers();

		//frame rate control
		long long loop_time = frameClock.split();
		auto actualTimeDiff = (target_time * 1000 - loop_time);
		auto differance = actualTimeDiff - sleep_correction; //clock in micro-> frames in mili
		if (differance > 0)
		{
			std::this_thread::sleep_for(std::chrono::microseconds(differance));
			//after sleep figure out how off we were and adjust
			long long new_loop_time = frameClock.split();
			sleep_correction += (new_loop_time - target_time * 1000); //convert to miliseconds
		}

		if (actualTimeDiff < 0)
		{
			//LM.writeLog("GameManager::run:Running slower that target fps of: %f, actual fps was %f, actual time differance: %f!", convertToFPS(target_time), convertToFPS(loop_time/1000), actualTimeDiff/1000 );
			//reset sleep correction
			sleep_correction = 0;
		}

		if (steps.getStepCount() % 60 == 0)
		{
			//LM.writeLog("GameManager::run:Fps: %f!", 1.0f / (frameClock.split() / 1000000.0f));
			std::cout << "GameManager::run:Fps: " << 1.0f / (frameClock.split() / 1000000.0f) << '\n';
		}
			

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
	d *= 1000;//in miliseconds need seconds
	return d;
}

