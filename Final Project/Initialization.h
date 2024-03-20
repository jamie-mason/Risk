#ifndef INITIALIZATION_H
#define INITIALIZATION_H

#include "MapLoader.h"
#include "Player.h"
#include "Deck.h"
#include "Human.h"
#include <iostream>
#include <cstdlib> 
#include <vector>
#include <string>
#include <fstream>
#include <sys/stat.h>
#include <limits>
#include <algorithm>
#include <typeinfo>
#include <sstream>
#include <stdexcept>

class Initialization {
private:
    std::string mapDirectory = ""; // Directory containing map files
    Deck* currentDeck; // Current deck of the game
    std::vector<Player*> gamePlayers; // Vector containing game players
    MapLoader* loadedMap; // Loaded map for the game
    int numMaps; // Number of maps

    void clearScreen(); // Clears the console screen
    int getUserInputInteger(std::string output, int min, int max); // Helper function for getting user integer input
    std::string getUserInputString(std::string output, std::string choice1, std::string choice2); // Helper function for getting user string input
    std::vector<std::string> getAndDisplayMapOptions(); // Displays all available maps
    void chooseMap(); // Gets user input for choosing an available map
    std::vector<Map*> chooseSeveralMaps(); // Allows the user to choose multiple maps
    void createPlayers(); // Gets input from the user for the amount of players to be created

public:
    Initialization(); // Constructor for Initialization
    Initialization(bool createPlayersFlag); // Constructor for Initialization with an option to create players
    Initialization(int num); // Constructor for Initialization with a specified number of maps
    Deck* getDeck(); // Returns the current deck
    std::vector<Player*> getPlayers(); // Returns the game players
    Map* getMap(); // Returns the loaded map
};

#endif // INITIALIZATION_H
