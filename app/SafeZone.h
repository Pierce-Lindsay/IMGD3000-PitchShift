#pragma once
#include <vector>
#include "../engine/audio/Music.h"
#include "../engine/Clock.h"

/// <summary>
/// Class for handling the safe zone position over time according to the music and a list of safe positions.
/// </summary>
class SafeZone
{
private:
	const float DEFAULT_SAFE_ZONE_WIDTH = 20.0f;
	const float DEFAULT_MIN_SAFE_ZONE_WIDTH = 4.0f;
	int size = 0; // 1/2 second positions
	std::vector<float>& safePositions;
	bool finished = false;
	bool started = false;
	float positionSpacingSeconds = 0; //how many seconds between each position in the list
	df::Music* music = nullptr; //music to sync with
	float width = DEFAULT_SAFE_ZONE_WIDTH; //width of the safe zone
	df::Clock clock; //clock to track time since start
	const float LEVEL_UP_TIME = 15000.0f; //time in ms after which the safe zone levels up (decreases in size)
	const float LEVEL_UP_DECREASE = 2.0f; //amount to decrease the safe zone width after each level up
	int level = 1; //current level of the safe zone, increases every LEVEL_UP_TIME

	/// <summary>
	/// Linear interpolation between a and b with t in [0,1].
	/// </summary>
	static float lerp(float a, float b, float t);

	
public:

	/// <summary>
	/// Start the music and the movement of the safe zone. Position fo safe zone will be determined by the music time
	/// and safe zone positions (iterpolates).
	/// </summary>
	void start();

	/// <summary>
	/// Updates the safe zone status (whether finished or not) depending on the music status.
	/// Should be called each frame.
	/// </summary>
	void update();

	/// <summary>
	/// Get the current position of the safe zone (x coordinate) depending on the music time.
	/// </summary>
	float getSafeZone();

	/// <summary>
	/// Get the the direction the spawn zone will move in at the current music time.
	/// </summary>
	/// <returns>-1 for left or 1 for right, and return 0 on music time error.</returns>
	int getSafeZoneDeltaDirection();

	/// <summary>
	/// Create a safe zone with the given list of safe positions 
	/// (in x coordinates), the spacing in seconds between each position, and the music to sync with.
	/// </summary>
	SafeZone(std::vector<float>& safePositions, float positionSpacingSeconds, df::Music* music);

	/// <summary>
	/// Is the safe zone finished (music ended and no more safe zone)?
	/// </summary>
	bool isFinished() const;

	/// <summary>
	/// Has the safe zone started moving and the music started playing?
	/// </summary>
	/// <returns></returns>
	bool hasStarted() const;

	/// <summary>
	/// Get the width of the safe zone.
	/// </summary>
	float getWidth() const;

	/// <summary>
	/// Set the width of the safe zone.
	/// </summary>
	void setWidth(float width);

	/// <summary>
	/// Gets the current time in the music in milliseconds from the start, 0 if music hasn't started 
	/// and 0 if music is finished.
	/// </summary>
	float getMusicTime() const;

	/// <summary>
	/// Stop the music!
	/// </summary>
	void stopMusic();
};