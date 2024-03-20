#include "MapLoader.h"
#include <iostream>
#include <stdexcept>
#include <time.h>
#include "Initialization.h"
#include "Startup.h"
#include "MainLoop.h"
#include "Human.h"
#include <filesystem>


void clearScreen() {
#ifdef _WIN32
	std::system("cls"); // Clear the console screen on Windows
#else
	// Assume Unix-like system
	std::system("clear"); // Clear the console screen on Unix-like systems
#endif
}
void GameDriver() {
	srand(time(NULL));
	Initialization ini;                                //initialization object
	Startup startup(ini.getPlayers(), ini.getMap());   //startup object
	MainLoop mainLoop(ini.getPlayers() ,ini.getMap(), ini.getDeck(), 3); //mainloop object
	clearScreen();      //clear the screen
	mainLoop.play();   //calls the mainloop play function
}
int main()
{
	GameDriver();  //calls the game driver function

	return 0;    //returns the main function at 0
}


