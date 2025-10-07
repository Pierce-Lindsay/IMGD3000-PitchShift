Pierce Lindsay (ptlinday@wpi.edu), Hung Dao (hdao@wpi.edu)
IMGD 3000
Professor Claypool
10/6/2025

Dragonfly Game Engine Project 3

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

	-The project is structured into four folders: app, engine, assets, and tests. Engine contains all the
	required code for Project2 sorted into folders based on catergories. Aduio class are in audio, graphics related classes are in graphics, etc.
	App contains the entry point and the game Pitch SHift. Assets contains the fonts, sounds, sprites, and music organized into subfolders..

	-In main, the test class is called and it handles all the unit tests and then runs a an
	integrated test that tests specific functionalities that can't be tested with unit tests easily
	such as input and display. It is up to the viewer to determine if everything looks and works right on
	these tests.

Running/Experience:

	-When running the project, almost all test outputs and logging will be outputed to a log
	file at default relative path $(SolutionDir)logs\dragonfly_log.txt. This is with a few
	exceptions. You'll notice some tests are not shown in the log file (1-5) that's because
	these tests involve shutting down/starting the log manager. The log manager is supposed 
	to overwrite the file on every new start so this is expected and a compromise for keeping
	almost everything in the logs. Additionally after all unit tests are ran, integrated tests
	that may expect user interaction will start.

Differences from the recommended architecture:
	
	-The slides shown in class recommend microseconds for the clock implementation while the
	ruberic reccomens milliseconds. I went in the middle and used microseconds for my clock
	but milliseconds in the GameManager for most frame-related code.

	-The names of events are slightly different. Instead of using df::out, I make the string
	"out" and place it in the namespace df. It didn't amke sense to my why the namespace name was
	placed in the string.

	-I reordered and added more key_codes to be more in line with the key_codes offered by SFML.

	-The structure of the projects folders is different as highlighted earlier.

A final note on the unit tests:
	
	The unit tests attempt to test almost everything that can be tested with booleans/math.
	They test a lot of logic but fail to test the dispay for certain items and inputs as
	these require an actual integrated environment. For testing these specific items, 
	integrated tests at the end are used. Whether everything functions properly is then
	at the opinion of the viewer/user.