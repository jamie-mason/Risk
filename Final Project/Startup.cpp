#include "Startup.h"

void Startup::clearScreen() {
#ifdef _WIN32
	std::system("cls"); // Clear the console screen on Windows
#else
	// Assume Unix-like system
	std::system("clear"); // Clear the console screen on Unix-like systems
#endif
} //closes the function definition

void Startup::displayPlayersCountriesAndArmies(Player* thePlayer) {
	// Print header
	std::cout << std::setw(3) << "Num" << " | " << std::setw(25) << "Country Owned" << " | " << std::setw(6) << "Armies" << " | " << std::setw(25) << "Bordering Countries" << " | " << std::setw(6) << "Armies" << std::endl;

	// Iterate over countries owned by the player
	for (int i = 0; i < thePlayer->getCountries().size(); i++) {
		// Get current country owned by the player
		Country* currCountry = thePlayer->getCountries()[i];
		// Print country information
		std::cout << std::setw(3) << i + 1 << " | " << std::setw(25) << currCountry->getName() << " | " << std::setw(6) << currCountry->getArmies() << " | ";

		// Iterate over bordering countries
		for (int j = 0; j < currCountry->getBorderingCountries().size(); j++) {
			// Get current bordering country
			Country* bordering = currCountry->getBorderingCountries()[j];
			// Check if it's the first bordering country
			if (j == 0) {
				// Print bordering country information
				std::cout << std::setw(25) << bordering->getName() << " | " << std::setw(6) << bordering->getArmies() << std::endl;
			}
			else {
				// Print empty row for subsequent bordering countries
				std::cout << std::setw(3) << "" << " | " << std::setw(25) << "" << " | " << std::setw(6) << "" << " | " << std::setw(25) << bordering->getName() << " | " << std::setw(6) << bordering->getArmies() << std::endl;
			}
		}
	}
}


int Startup::getUserInputInteger(std::string output, int min, int max) {
	int input = 0; // Variable to store the user input integer

	while (input < min || input > max) {
		std::cout << output;
		if (!(std::cin >> input)) {
			std::cout << "Invalid input! Must be an integer." << std::endl;
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		if (input == -1) {
			std::cout << "Quitting..." << std::endl;
			exit(1);
		}
		if (input < min || input > max) {
			std::cout << "Invalid input! Integer must be in the range [" << min << ", " << max << "]." << std::endl << std::endl;
		}
	}

	return input;
}

Startup::Startup(std::vector<Player*> players, Map* map) {
	playerOrder = players;
	currMap = map;
	randomPlayerOrder();
	assignPlayerCountries();
	assignArmiesAI();

} //closes the function definition
Startup::Startup(std::vector<Player*> players, Map* map, bool quickStart) {
	if (!quickStart) {
		//Startup(players, map);
	}
	else {
		playerOrder = players;
		currMap = map;
		randomPlayerOrder();

		// Assign countries randomly
		size_t countriesAssigned = 0;
		int playerIndex = 0;

		while (countriesAssigned < currMap->getCountries().size()) {
			int countryIndex = rand() % currMap->getCountries().size();
			if (currMap->getCountries()[countryIndex]->getOwner() == NULL) {
				countriesAssigned += 1;
				currMap->getCountries()[countryIndex]->setOwner(playerOrder[playerIndex]);
				playerOrder[playerIndex]->addCountry(currMap->getCountries()[countryIndex]);
				playerIndex = (playerIndex + 1) % playerOrder.size();
			}
		}

		// Spread player armies evenly
		int numArmies[6] = { 0, 40, 35, 30, 25, 20 };

		for (Player* player : playerOrder) {
			std::vector<Country*> playerCountries = player->getCountries();
			size_t countryIndex = 0;
			int armiesToPlace = numArmies[playerOrder.size() - 1];

			while (armiesToPlace > 0) {
				playerCountries[countryIndex]->addArmies(1);
				armiesToPlace--;
				if (countryIndex + 1 == playerCountries.size())
					countryIndex = 0;
				else
					countryIndex++;
			}
		}
	}
} //closes the function definition
//Assign a random player order
void Startup::randomPlayerOrder() {
	std::cout << "\n*ASSIGNING RANDOM PLAYER ORDER*" << std::endl; //Outputs prompt then ends the line.
	int ind1, ind2;  //defines two integer variables

	std::srand(static_cast<unsigned int>(std::time(nullptr)));  // Seeds the random number generator with the current time
	for (int i = 0; i < 100; i++) {  //defines a loop where index i will increment until the condition is no longer true.
		ind1 = std::rand() % playerOrder.size();  //set the variable to a random value between 0 and the playerOrder vector size.
		ind2 = std::rand() % playerOrder.size();    //set the variable to a random value between 0 and the playerOrder vector size.

		//swaps the two values in the vector order.
		Player* tempPlayer = playerOrder[ind1];
		playerOrder[ind1] = playerOrder[ind2];
		playerOrder[ind2] = tempPlayer;
	} //clolses the for-loop

	std::cout << "\nCurrent player order: " << std::endl;   //Outputs prompt then ends the line.
	//prints the player order;
	for (int i = 0; i < playerOrder.size(); i++) {
		std::cout << "\t" << (i + 1) << ": " << playerOrder[i]->getID() << std::endl;
	} //clolses the for-loop
}  //closes the function definition

void Startup::assignPlayerCountries() {
	std::cout << "\n*ASSIGNING RANDOM COUNTRIES TO PLAYERS*" << std::endl;   //Outputs prompt then ends the line.
	int numCountriesAssigned = 0, currPlayerIndex = 0, countryIndexToAssign;   // defines integer variables and sets some of their values.
	std::srand(static_cast<unsigned int>(std::time(nullptr)));   // Seeds the random number generator with the current time
	// Pick a random country, if it's not taken give it to the proper player
	do {
		countryIndexToAssign = rand() % currMap->getCountries().size(); // Randomly selects an index within the range of available countries

		if (currMap->getCountries()[countryIndexToAssign]->getOwner() == NULL) { // Checks if the country at the randomly selected index has no owner
			numCountriesAssigned += 1; // Increments the count of countries assigned

			currMap->getCountries()[countryIndexToAssign]->setOwner(playerOrder[currPlayerIndex]); // Assigns the current player as the owner of the selected country
			playerOrder[currPlayerIndex]->addCountry(currMap->getCountries()[countryIndexToAssign]); // Adds the selected country to the current player's list of countries
			currPlayerIndex = (currPlayerIndex + 1) % playerOrder.size(); // Moves to the next player in the player order
		}
	} while (numCountriesAssigned < currMap->getCountries().size()); // Loop until all countries are assigned to players

	std::cout << "\nCurrent countries assigned: " << std::endl; // Prints a header for the list of countries assigned to players
	for (int i = 0; i < playerOrder.size(); i++) { // Iterates over each player in the player order
		std::cout << std::endl << playerOrder[i]->getName() << "(" << playerOrder[i]->getCountries().size() << " countries): " << std::endl; // Prints player's name and the number of countries they own
		for (int j = 0; j < playerOrder[i]->getCountries().size(); j++) { // Iterates over each country owned by the player
			std::cout << "\t" << playerOrder[i]->getCountries()[j]->getName() << std::endl; // Prints the name of the country owned by the player
		}//clolses the for-loop
	} //clolses the for-loop

}
//assigns the players armies
void Startup::assignPlayerArmies() { // Declares the beginning of the function definition
	const int numArmiesSize = 6, numArmiesAdded = 1; // Declares constant variables for the size of the armies array and the number of armies to be added per country
	std::cout << "\n*ASSIGNING ARMIES TO COUNTRIES*" << std::endl; // Prints a message to indicate the beginning of the army assignment process

	int numArmies[numArmiesSize] = { 0, 40, 35, 30, 25, 20 }, // Declares and initializes an array with predefined numbers of armies for different players
		totalTokens = numArmies[playerOrder.size() - 1] * playerOrder.size(), // Calculates the total number of tokens based on the number of players and the maximum number of armies
		currPlayerIndex = 0, // Initializes a variable to keep track of the index of the current player
		countryNumber; // Declares a variable to store the number of the selected country

	std::map<std::string, int> playerArmies; // Declares a map to store the number of armies each player has

	for (int i = 0; i < playerOrder.size(); i++) { // Iterates over the players in the player order
		playerArmies[playerOrder[i]->getName()] = numArmies[playerOrder.size() - 1]; // Initializes the number of armies for each player
	}   //clolses the for-loop

	for (int i = 0; i < currMap->getCountries().size(); i++) { // Iterates over the countries in the map
		currMap->getCountries()[i]->addArmies(numArmiesAdded); // Adds a predefined number of armies to each country
		totalTokens -= numArmiesAdded; // Decrements the total number of tokens
		playerArmies[currMap->getCountries()[i]->getOwner()->getName()] -= 1; // Decrements the number of armies for the owner of each country
	}   //clolses the for-loop

	do { // Enters a do-while loop to iterate until all tokens are used
		Player* currPlayersTurn = playerOrder[currPlayerIndex]; // Retrieves the current player's turn

		if (playerArmies[currPlayersTurn->getName()] > 0) { // Checks if the current player has any armies left to place
			std::cout << "\nCurrent player to place an army unit (" << playerArmies[currPlayersTurn->getName()] << " left): " << currPlayersTurn->getName() << std::endl << "\t"; // Prints a message indicating the current player and the number of armies they have left
			displayPlayersCountriesAndArmies(currPlayersTurn); // Calls a function to display the countries owned by the current player and the number of armies in each country
			countryNumber = getUserInputInteger("Your choice (-1 to quit): ", 1, currPlayersTurn->getCountries().size()); // Prompts the user to choose a country to place armies
			currPlayersTurn->getCountries()[countryNumber - 1]->addArmies(numArmiesAdded); // Adds a predefined number of armies to the selected country
			totalTokens -= numArmiesAdded; // Decrements the total number of tokens
			playerArmies[currPlayersTurn->getName()] -= numArmiesAdded; // Decrements the number of armies for the current player
		} //closed the if statement

		currPlayerIndex = (currPlayerIndex + 1) % playerOrder.size(); // Moves to the next player's turn, cycling back to the first player if necessary
	} while (totalTokens > 0); // Continues the loop until all tokens are used
} // Closes the function definition

void Startup::assignArmiesAI() {
	std::cout << std::endl << "*ASSIGNING ARMIES TO COUNTRIES*" << std::endl;
	int numArmies[6] = { 0, 40, 35, 30, 25, 20 };
	int totalTokens = numArmies[playerOrder.size() - 1] * playerOrder.size();
	int currPlayerIndex = 0;
	std::map<std::string, int> playerArmies;

	for (int i = 0; i < playerOrder.size(); i++) {
		playerArmies[playerOrder[i]->getName()] = numArmies[playerOrder.size() - 1];
	}

	// Assign one army to every country
	for (int i = 0; i < currMap->getCountries().size(); i++) {
		currMap->getCountries()[i]->addArmies(1);
		totalTokens -= 1;

		playerArmies[currMap->getCountries()[i]->getOwner()->getName()] -= 1;
	}
} //closes the function definition
std::vector<Player*> Startup::getPlayerOrder() {
	return playerOrder;
} //closes the function definition

Startup::~Startup() {
	delete currMap;
}