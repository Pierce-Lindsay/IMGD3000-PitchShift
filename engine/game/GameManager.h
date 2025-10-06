#pragma once
#include "../Manager.h"
#include "../Clock.h"

#define GM df::GameManager::GetInstance()
namespace df {

	/// <summary>
	/// A class for managing running the game in a game engine, handles all the other managers.
	/// </summary>
	class GameManager : public Manager
	{
	private:
		const int FRAME_LENGTH = 33; //miliseconds
		bool game_over = false;
		int target_time = FRAME_LENGTH; //target frame time in miliseconds
		int sleep_correction = 0; //correction in microseconds for accuracy
		long long delta_time = 0.0f; //time the last frame took in miliseconds
		Clock frameClock;
		//singleton stuff
		GameManager();
		GameManager(GameManager const& copy);
		void operator=(GameManager const& assign);

		/// <summary>
		/// Converts a given frame time in miliseconds to an fps in seconds.
		/// </summary>
		double convertToFPS(int frame_Length); //in miliseconds

	public:
		/// <summary>
		/// Destroys the game and any other dependencies.
		/// </summary>
		~GameManager();

		/// <summary>
		/// Get instance of the one and only GameManager.
		/// </summary>
		/// <returns></returns>
		static GameManager& GetInstance();

		/// <summary>
		/// Start up GameManager and required dependencies.
		/// </summary>
		/// <returns>0 if successful.</returns>
		int startUp() override;

		/// <summary>
		/// Shut down GameManager and required dependencies.
		/// </summary>
		void shutDown() override;

		/// <summary>
		/// Runs the game -> starts the gam eloop
		/// </summary>
		void run();

		/// <summary>
		/// Sets if the game should end, true by default, notifies the game loop if set to true.
		/// </summary>
		void setGameOver(bool game_over = true);

		/// <summary>
		/// Gets the current game over status.
		/// </summary>
		bool getGameOver() const;

		/// <summary>
		/// Returns the target time for the game loop in miliseconds.
		int getFrameTime() const;

		/// <summary>
		/// Returns the time the last frame took in miliseconds.
		/// </summary>
		long long getDeltaTime() const;
	};
}