#include "Initialization.h"
#include <filesystem>

// Function to clear the console screen
void Initialization::clearScreen() {
#ifdef _WIN32
    std::system("cls"); // Clear the console screen on Windows
#else
    // Assume Unix-like system
    std::system("clear"); // Clear the console screen on Unix-like systems
#endif
}

// Function to get an integer input from the user within a specified range
int Initialization::getUserInputInteger(std::string output, int min, int max) {
    int input = 0; // Variable to store the user input integer

    while (input < min || input > max) {
        std::cout << output;
        if (!(std::cin >> input)) {
            if (input >= INT_MIN && input <= INT_MAX) {
                std::cout << "Invalid input! Must be an integer. Not a long Integer " << std::endl;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
            else {
                std::cout << "Invalid input! Must be an integer." << std::endl;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
        }
        if (input == -1) {
            std::cout << "Quitting..." << std::endl;
            exit(1);
        }
        if (input < min || input > max) {
            std::cout << "Invalid input! Integer must be in the range [" << min << ", " << max << "]." << std::endl<<std::endl;
        }
    }

    return input;
}

// Function to get and display the list of map options available
std::vector<std::string> Initialization::getAndDisplayMapOptions() {
    std::vector<std::string> mapFiles; // Vector to store the names of map files
    std::string directoryPath = std::filesystem::current_path().string();

    if (std::filesystem::exists(directoryPath) && std::filesystem::is_directory(directoryPath)) {
        for (const auto& entry : std::filesystem::directory_iterator(directoryPath)) {
            if (entry.is_regular_file() && entry.path().extension() == ".map") {
                mapFiles.push_back(entry.path().filename().string());
            }
        }

        if (mapFiles.empty()) {
            std::cout << "No map files found in the directory." << std::endl;
        }
        else {
            for (const auto& mapFile : mapFiles) {
                std::cout << "MAP FILE: " << mapFile << std::endl;
            }
        }
    }
    else {
        std::cerr << "Directory not found: " << directoryPath << std::endl;
    }

    return mapFiles;
}

// Function to choose a map from the available options
void Initialization::chooseMap() {
    std::cout << std::endl << "*CHOOSING MAP*" << std::endl;

    std::vector<std::string> mapFiles = getAndDisplayMapOptions();
    int mapNumber = 0;
    std::string* getIntegerPrompt = new std::string("Your choice (" + std::to_string(1) + " to " + std::to_string(mapFiles.size()) + " or - 1 to quit) : ");
    if (!mapFiles.empty()) {
        mapNumber = getUserInputInteger(*getIntegerPrompt, 1, mapFiles.size());
    }
    else {
        std::cerr << "No map files found. Exiting..." << std::endl;
        exit(1);
    }

    MapLoader* map = new MapLoader();
    bool validMap = false;
    std::string error;

    try {
        map->parseMap(mapDirectory + mapFiles[mapNumber - 1]);
        validMap = true;
    }
    catch (std::invalid_argument& e) {
        error = e.what();
    }

    while (!validMap) {
        clearScreen();
        std::cout << error << std::endl;
        std::cout << "Invalid map, choose another map: " << std::endl;
        getAndDisplayMapOptions();
        mapNumber = getUserInputInteger("Your choice: ", 0, mapFiles.size());

        try {
            map->parseMap(mapDirectory + mapFiles[mapNumber - 1]);
            validMap = true;
        }
        catch (std::invalid_argument& e) {
            error = e.what();
        }
    }

    loadedMap = map;
    delete getIntegerPrompt;
}

std::vector<Map*> Initialization::chooseSeveralMaps() {
    std::cout << std::endl << "*CHOOSING MAP*" << std::endl; // Display message indicating map selection process
    std::vector<std::string> mapFiles = getAndDisplayMapOptions(); // Get and display available map options, store in vector
    std::vector<Map*> mapsSelected; // Vector to store selected maps
    std::vector<int> choices; // Vector to track user's choices
    for (int i = 0; i < numMaps; i++) { // Loop through the number of maps the user wants to select
        int mapNumber = getUserInputInteger("Select Map " + std::to_string(i + 1) + " (-1 to quit): ", 1, mapFiles.size()); // Get user's map selection

        MapLoader* map = new MapLoader(); // Create a new instance of MapLoader to load selected map

        bool validMap = false; // Flag to track if the selected map is valid
        std::string error; // String to store error message if map selection fails

        // Try to parse the selected map
        try {
            map->parseMap(mapFiles[mapNumber - 1]); // Parse the selected map
            validMap = true; // If successful, mark the map as valid
        }
        // Catch any invalid argument exceptions (e.g., invalid map format)
        catch (std::invalid_argument e) {
            error = e.what(); // Store the error message
        }

        // Check if the map has already been selected
        if (std::find(choices.begin(), choices.end(), mapNumber) != choices.end()) {
            validMap = false; // Mark the map as invalid
            error = "Map already selected."; // Set the error message
        }

        // Repeat until a valid map is selected
        while (!validMap) {
            clearScreen(); // Clear the screen to provide a clean interface for map selection
            std::cout << error; // Display the error message from the previous attempt
            std::cout << "Invalid map, choose another map: " << std::endl; // Prompt user to choose another map
            getAndDisplayMapOptions(); // Display available map options again
            mapNumber = getUserInputInteger("Select Map " + std::to_string(i + 1) + " : ", 1, mapFiles.size()); // Get user's map selection again

            // Try to parse the newly selected map
            try {
                map->parseMap(mapDirectory + mapFiles[mapNumber - 1]); // Parse the newly selected map
                validMap = true; // If successful, mark the map as valid
            }
            // Catch any invalid argument exceptions (e.g., invalid map format)
            catch (std::invalid_argument e) {
                error = e.what(); // Store the error message
            }

            // Check if the map has already been selected
            if (std::find(choices.begin(), choices.end(), mapNumber) != choices.end()) {
                validMap = false; // Mark the map as invalid
            }
        }

        choices.push_back(mapNumber); // Add the selected map number to the choices vector
        mapsSelected.push_back(map->getMap()); // Add the parsed map to the selected maps vector
    }

    return mapsSelected; // Return the vector of selected maps
}


void Initialization::createPlayers() {
    std::cout << std::endl << "*CHOOSING AMOUNT OF PLAYERS*" << std::endl; // Display message indicating player creation process
    std::cout << "Select amount of players (2 - 6): " << std::endl; // Prompt user to select number of players
    int numPlayers = getUserInputInteger("Your choice (-1 to quit): ", 2, 6); // Get user's choice for number of players
    std::cout << "Creating players..." << std::endl; // Notify user that players are being created

    // Create a deck with the number of countries on the loaded map
    currentDeck = new Deck(loadedMap->getMap()->getCountries().size());

    // Create players based on the selected number
    for (int i = 0; i < numPlayers; i++) {
        std::cout << "Created Player " << (i + 1) << "..." << std::endl; // Notify user that a player has been created
        Player* currPlayer = new Human("Player " + std::to_string(i + 1)); // Create a new Human player
        gamePlayers.push_back(currPlayer); // Add the created player to the list of game players
    }
}

Initialization::Initialization() {
    chooseMap(); // Choose a map for the game
    std::cout << std::endl << "Successfully chose a map, creating the game state..." << std::endl; // Notify user that a map has been successfully chosen
    createPlayers(); // Create players for the game
    numMaps = 1; // Set the number of maps to 1
}

Initialization::Initialization(bool cPlayer) {
    chooseMap(); // Choose a map for the game
    std::cout << std::endl << "Successfully chose a map, creating the game state..." << std::endl; // Notify user that a map has been successfully chosen
    if (cPlayer)
        createPlayers(); // Create players for the game if specified
    else
        currentDeck = new Deck(loadedMap->getMap()->getCountries().size()); // Create a deck with the number of countries on the loaded map
    numMaps = 1; // Set the number of maps to 1
}

Initialization::Initialization(int n) {
    numMaps = n; // Initialize the number of maps
}

Deck* Initialization::getDeck() {
    return currentDeck; // Return the deck for the game
}

std::vector<Player*> Initialization::getPlayers(){
    return gamePlayers; // Return the list of players for the game
}

Map* Initialization::getMap(){
    return loadedMap->getMap(); // Return the loaded map for the game
}
