#include "Reinforcement.h"      //References the Reinforcement header file.


int Reinforcement::staticBonusArmies = 0;

int Reinforcement::calculateCountryBonus(Player* player) {
	return player->getCountries().size() / 3; //returns the quotient of countries divided by 3.
}

int Reinforcement::calculateContinentBonus(Player* player, std::vector<Continent*> continents) {
	int bonusPoints = 0; // Initialize bonusPoints variable.

	// Iterate over continents
	for (const auto& currContinent : continents) {
		size_t check = 0; // Initialize check variable.
		const std::vector<Country*>& continentsCountries = currContinent->getCountries(); // Get countries of the current continent.

		// Iterate over countries of the current continent
		for (const auto& currCountry : continentsCountries) {
			if (currCountry->getOwner() == player) {
				check++; // Increment check if the player owns the current country.
			}
			else {
				break; // Break loop if the player does not own the current country.
			}
		}

		// Check if the player owns all countries in the current continent
		if (check == continentsCountries.size()) {
			bonusPoints += currContinent->getWorth(); // Add continent worth to bonusPoints.
		}
	}

	return bonusPoints; // Return the total bonusPoints.


}

int Reinforcement::calculateCardBonus(Player* player) {
	int numberOfCards = player->getHand()->getNumberOfCards(); // Get the number of cards in the player's hand.

	// Check if the player has less than 3 cards
	if (numberOfCards < 3) {
		return 0; // Return 0 bonus if the player has less than 3 cards.
	}

	// Check if the player has 5 cards
	if (numberOfCards == 5) {
		std::cout << "You have " << numberOfCards << " cards you need to exchange them" << std::endl; // Notify the player to exchange cards.
		return player->getHand()->SelectExchange(); // Perform card exchange and return the bonus.
	}

	// Prompt the player to view their cards if they have more than 3 cards
	std::cout << "You have " << numberOfCards << " cards would you like to view them? (y/n)";
	std::string answer;
	std::cin >> answer;

	// Check if the player wants to view their cards
	if (answer == "y" || answer == "Y") {
		return player->getHand()->SelectExchange(); // Perform card exchange and return the bonus.
	}

	return 0; // Return 0 bonus if the player does not want to view their cards.
}


int Reinforcement::calculateMaxCardBonus(Player* player) {
	return player->getHand()->getAnyExchange();
}

void Reinforcement::startReinforcementPhase(Player* player) {
	notify(player, "Reinforcement", "");
}

int Reinforcement::getUserInputInteger(std::string output, int min, int max) {
	int input = 0; // Variable to store the user input integer
		while (input < min || input > max) {
			std::cout << output;
			if (std::cin >> input) {
				if(input < min || input > max) {
					std::cout << "Invalid input! Integer must be in the range [" << min << ", " << max << "]." << std::endl << std::endl;

					continue;
				}
				
			}
			else if(input >= INT_MIN && input <= INT_MAX){
				std::cout << "Invalid input! Must be an integer. Not a long Integer " << std::endl;
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			}
			else {
				std::cout << "Invalid input! Must be an integer. " << std::endl;
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			}
		}

	return input;
}
void Reinforcement::executePlayerReinforcement(Player* player, std::vector<Continent*> continents) {
	startReinforcementPhase(player); // Initiates the reinforcement phase for the player.

	int bonusArmies = 0; // Initializes the variable to track bonus armies.
	int temp = 0; // Temporary variable to store the previous bonus count.
	int countryIndex = 0, armiesToAdd = 0;
	std::string prompt, getUserInputOutput;

	// Lambda function to print the bonus and update temp
	auto printBonus = [&](const std::string& label) {
		std::cout << label << ": +" << bonusArmies - temp << std::endl; // Print the bonus difference.
		temp = bonusArmies; // Update temp with current bonus count.
		};

	bonusArmies += calculateCountryBonus(player); // Calculate country bonus and update bonusArmies.
	printBonus("Country Bonus"); // Print and update temp with the country bonus.

	bonusArmies += calculateContinentBonus(player, continents); // Calculate continent bonus and update bonusArmies.
	printBonus("Continent Bonus"); // Print and update temp with the continent bonus.

	bonusArmies += calculateCardBonus(player); // Calculate card bonus and update bonusArmies.
	printBonus("Card Bonus"); // Print and update temp with the card bonus.

	// Loop to place reinforcements until all bonus armies are placed
	do {
		int numberOfCountries = player->getCountries().size(); // Get the number of countries owned by the player.
		std::cout << "Selection\t| Country name\t| Number of armies" << std::endl; // Display table headers.

		// Loop to display country details
		for (size_t i = 0; i < numberOfCountries; ++i) {
			auto country = player->getCountries()[i]; // Get the country object.
			std::cout << i + 1 << "\t| " << country->getName() << "\t| " << country->getArmies() << std::endl; // Display country details.
		}

		 // Variables to store user input for country index and armies to add.
		getUserInputOutput = "Select which country you would like to reinforce: ";
		// Loop to get valid country index from user
		countryIndex = getUserInputInteger(getUserInputOutput, 1, numberOfCountries);
		
		std::cout << "You have " << bonusArmies << " unplaced armies" << std::endl; // Display remaining bonus armies.

		// Loop to get valid number of armies to add to the selected country
		do {
			std::cout << "How many armies would you like to add to " << player->getCountries()[countryIndex - 1]->getName() << ": "; // Prompt for armies to add.
			std::cin >> armiesToAdd; // Read user input for armies to add.
			if (armiesToAdd < 0 || armiesToAdd > bonusArmies) // Check if input is valid.
				std::cout << "Select a valid number" << std::endl; // Display error message.
		} while (armiesToAdd < 0 || armiesToAdd > bonusArmies); // Repeat until valid input is provided.

		auto targetCountry = player->getCountries()[countryIndex - 1]; // Get the selected country object.
		prompt = "Reinforcing " + targetCountry->getName() + "'s " +
			std::to_string(targetCountry->getArmies()) + " armies with " + std::to_string(armiesToAdd) + " armies."; // Construct reinforcement message.

		notifyObserver(player, prompt); // Notify observer (likely the player) about the reinforcement.

		bonusArmies -= armiesToAdd; // Deduct the placed armies from bonusArmies.
		targetCountry->addArmies(armiesToAdd); // Add the armies to the selected country.
	} while (bonusArmies > 0); // Repeat until all bonus armies are placed.

}

void Reinforcement::reinforceCountry(Player* player, Country* country, int numArmies) {
	if (numArmies <= staticBonusArmies) { // Check if there are enough bonus armies to place
		if (!player) { // Check if the player is valid (not NULL)
			std::cout << "Invalid player." << std::endl; // Print error message
			return; // Exit the function
		}

		if (!country) { // Check if the country is valid (not NULL)
			std::cout << "Invalid country." << std::endl; // Print error message
			return; // Exit the function
		}

		if (numArmies < 1) { // Check if the number of armies to move is less than 1
			std::cout << "Need one or more armies to move." << std::endl; // Print error message
			return; // Exit the function
		}

		country->addArmies(numArmies); // Add armies to the country
		staticBonusArmies -= numArmies; // Decrease the number of remaining bonus armies

		// Create a message about the reinforcement action and the remaining bonus armies
		std::string prompt = "Reinforcing " + country->getName() + " with " + std::to_string(numArmies) + " armies.... " +
			std::to_string(staticBonusArmies) + " remaining bonus armies to place.";
		notifyObserver(player, prompt); // Notify the observer (probably the player) with the message
	}
	else {
		std::cout << "Not enough armies to place." << std::endl; // Print error message
	}


}

int Reinforcement::calculateTotalBonusArmies(Player* player, std::vector<Continent*> continents) {
	int bonusArmies = 0;

	// calculate number of reinforcements
	bonusArmies += calculateCountryBonus(player);
	bonusArmies += calculateContinentBonus(player, continents);
	bonusArmies += calculateMaxCardBonus(player);

	return bonusArmies;
}

void Reinforcement::notifyObserver(Player* player, std::string prompt) {
	notify(player, "Reinforcement", prompt);
}
