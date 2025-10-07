Pierce Lindsay (ptlinday@wpi.edu), Hung Dao (hdao@wpi.edu)
IMGD 3000
Professor Claypool
10/06/2025

Dragonfly Game Engine Project 3 - Alpha
Pitch Shift

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
		-Finally, the configuration expects to find debug DLLs at: PATH=%PATH%;..\SFML-3.0\bin

	-The project should be able to be complied with ctrl-shift-B or f5 to compile and run.

Project structure:

	-The game project is located in the app folder, and the Engine is located in the engine folder. All Assets are stored in the assets folder,
	divided into 4 subfolders: fonts, music, sounds, and sprites. The Tests are located in the tests folder, and the dragonfly.log file
	is located in the logs folder.

Running/Experience:

	-When running the project, almost all test outputs and logging will be outputed to a log
	file at default relative path $(SolutionDir)logs\dragonfly_log.txt. This is with a few
	exceptions. You'll notice some tests are not shown in the log file (1-5) that's because
	these tests involve shutting down/starting the log manager. The log manager is supposed 
	to overwrite the file on every new start so this is expected and a compromise for keeping
	almost everything in the logs. Additionally after all unit tests are ran, integrated tests
	that may expect user interaction will start.