Pitch Shift
Team Name: Team Aegean
Group Members: Hung Dao (hdao@wpi.edu), Pierce Lindsay (ptlindsay@wpi.edu)
Genre: Rhythm/Music Survival game
Engine: Pierce’s
IMGD 3000

Dragonfly Game Engine Project 3 - Final

Platform: Windows

Project configuration/dependencies:

	-To run compile the project, the SFML following dependencies need to be added: 
	The VS project file is configured to expect:
		-All configurations includes at: $(SolutionDir)../SFML-3.0/include
		-All configurations library files at: $(SolutionDir)../SFML-3.0/lib
		-The following .lib files must be with SFML:
			sfml-system-d.lib
			sfml-window-d.lib
			sfml-graphics-d.lib
			sfml-audio-d.lib
			sfml-network-d.lib
			Winmm.lib
			Ws2_32.lib
			sfml-system.lib
			sfml-window.lib
			sfml-graphics.lib
			sfml-audio.lib
			sfml-network.lib
		-Finally, the configuration expects to find DLLs at: PATH=%PATH%;..\SFML-3.0\bin

	-The project should be able to be complied with ctrl-shift-B or f5 to compile and run.

Project structure:

	- The game project is located in the app folder, and the Engine is located in the engine folder. All Assets are stored in the assets folder,
	divided into 4 subfolders: fonts, music, sounds, and sprites. The Tests are located in the tests folder, and the dragonfly.log file
	is located in the logs folder.

Running/Experience:

	- When running the project, almost all test outputs and logging will be outputed to a log
	file at default relative path $(SolutionDir)logs\dragonfly_log.txt. This is with a few
	exceptions. You'll notice some tests are not shown in the log file (1-5) that's because
	these tests involve shutting down/starting the log manager. The log manager is supposed 
	to overwrite the file on every new start so this is expected and a compromise for keeping
	almost everything in the logs. Additionally after all unit tests are ran, integrated tests
	that may expect user interaction will start.

Description

	- Pitch shift is a game that involves dodging projectiles while following the pitch shift of 
	the game’s music. The player can move left and right, and the movement speed changes in sync
	with the music's tempo/rhythm. While moving, projectiles that hit the player will end the 
	game if the player runs out of lives. The player must survive by lasting as long as they 
	can without dying. The game gets harder as the pitch changes more quickly, and thus the 
	player must dodge and react to pitch shifts faster. The game goes on indefinitely until 
	the player dies or quits. The player is assigned a score based on how far they progressed 
	and the difficulty level they were playing on. 

Technical features

	- The ability to move the character with responsiveness and good feeling controls.

	- The spawning of projectiles that hurt the player on collision with their character.

	- A level and point system that increases difficulty over time and rewards the player 
	 with more points for lasting longer. Different difficulties can be selected that 
	 change how many points the player gets. High scores are saved between runs of the application. 

	- Designing the locations where the projectiles will spawn to be in line with where the 
	  pitch isn’t (the safe zones are where the pitch is shifting towards) and changing 
	  projectile colors as the level increases.

	- Increasing the velocity of projectiles and decreasing the size of the safe zone as the 
	  level increases.

	- Allowing the player to teleport to the other side of the screen on large pitch change runs.

	- Color change in level to also indicate pitch shifts (danger zones / safe zones).

	- Arrows that move in the direction where the pitch is shifting visually.

Artistic assets

	- Player character (3 animation frames, size of 3x3).

	- Projectiles (2 x 3, 1 frame)

	- Portal design (3x5 with a 5-frame animation to make it look interesting).

	- Designing art for the floor of the 2D room that the player moves on. 
	 The floor will be split into different subsections that can change color 
	 (color will be used to help indicate pitch shift and safety). 
	 The sub-sections will have their own (7x1 frames with 10 frame animations).

	- Display text for tutorial and UI features 
	  (display test will be spectral and be high-altitude and use the drawstr() function.

	- Simple sounds for (player hit, portal use, UI selections, game loss). 
	  Sounds will be found from either previous projects or online.

	- Music to play during the game. May be found online or made depending on time constraints.

	- Separate music for the start-menu screen, which will be found online.

	- Game start sprite (62x7, 1 frame)

	- Game over (9x1, 1 frame)

	- Left arrow and right arrow(4 x1, 4 frames, 2 cooldown)

	- Title art (51 x 7, 4 frames)

Implementation plan

	- All implemented code will be custom-made by the group. The spawning of 
	  projectiles will be hard-coded on a per-song basis. The movement of the character 
	  will use simple input manager events to change the position of the player. Collision 
	  will be handled by the engine, and teleportation can use an out event. Color 
	  change will be coded as a function of the position of safety from projectiles 
	  and may also occur with the changing of pitch.

Work Distribution

	Hung Dao:
		Character: Design, Movement, Sounds
		Portal: Design, Teleport, Sounds
		Floor: Design, Color change
		UI: Tutorial, Title, Health Display
		Start menu music
		Game start screen and game over screen switching to game start
		Difficulty system
		Trailer

	Pierce Lindsay:
		Projectile: Design, Spawning, Color change, Level up logic
		Balencing
		Color changes to match music
		Level system
		Score system, High School Saving/Loading
		Game ending condition
		Arrows that indicate pitch changes
		Presentation materials/slideshow

Expansions/Design Changes:

	- Added a new difficulty: Practice (100 hits)

	- Changed Easy mode health to 5 hits instead of 3

	- Score system

	- Level system

	- Increased game difficulty over time

	- The game ending is now indefinite until the player loses

	- Arrows that indicate pitch changes

	- Projectile sprite design is no longer random; instead, the velocity is 
	  slightly random, and the color changes over time


How to play:

	Run the program, then press 'p' to play the game. Then use 'A' and 'D' or the 
	'left' and 'right' arrow keys to move the character left and right. Dodge the 
	projectiles by moving with the pitch shifts. You have to survive to the end of 
	the song, taking less than 2 hits. Press 'q' to quit the game at any time.

