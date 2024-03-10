#include <string>
#include <limits>
#include <cmath>
#include <iomanip> // for setw()
#include "Common.h" // Include necessary header file where the Common class is defined


void Common::displayPlayersCountriesAndArmies(Player* player) {
	// Print header for the table
	std::cout << std::setw(3) << "Num" << " | "
		<< std::setw(25) << "Country Owned" << " | "
		<< std::setw(6) << "Armies" << " | "
		<< std::setw(25) << "Bordering Countries" << " | "
		<< std::setw(6) << "Armies" << "\n";

	// Iterate over the player's countries
	for (int i = 0; i < player->getCountries().size(); i++) {
		// Get the current country
		Country* currCountry = player->getCountries()[i];
		// Print information about the current country
		std::cout << std::setw(3) << i + 1 << " | "
			<< std::setw(25) << currCountry->getName() << " | "
			<< std::setw(6) << currCountry->getArmies() << " | ";

		// Iterate over the bordering countries of the current country
		for (int j = 0; j < currCountry->getBorderingCountries().size(); j++) {
			// Get the bordering country
			Country* bordering = currCountry->getBorderingCountries()[j];
			// If it's the first bordering country, print its information
			if (j == 0) {
				std::cout << std::setw(25) << bordering->getName() << " | "
					<< std::setw(6) << bordering->getArmies() << "\n";
			}
			else {
				// If it's not the first bordering country, print empty cells for country-owned and armies columns
				std::cout << std::setw(3) << "" << " | "
					<< std::setw(25) << "" << " | "
					<< std::setw(6) << "" << " | "
					<< std::setw(25) << bordering->getName() << " | "
					<< std::setw(6) << bordering->getArmies() << "\n";
			}
		}
	}
}
int Common::getUserInputIntInRange(std::string prompt, int min, int max) {
	if (min < max) {
		int input; // Variable to store the user input integer
		do {
			// Output the specified message to the user
			std::cout << prompt;
			// Read user input integer
			if (std::cin >> input) {
				// Check if the user has chosen to quit
				if (input == -1) {
					std::cout << "Quitting..." << std::endl; // Notify the user
					exit(1); // Exit the program
				}
				if (input < min || input > max) {
					// If not, clear input stream, ignore remaining characters, and prompt the user again
					std::cin.clear();
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					std::cout << "Invalid input" << std::endl; // Notify the user of invalid input
					std::cout << "Integer input must be greater than or equal to " << min << " and less than or equal to" << max << "." << std::endl;   // Notify the user of the valid input range and integer requirement
				}

			}
			else {
				std::cout << "Invalid input!!!" << std::endl; // Notify the user of invalid input
				std::cout << "Must be an integer!!!" << std::endl; // Notify the user of the integer requirement
				input = min - 1;
				if (input == -1) {
					input = min - 1;
				}
			}

		} while (input < min || input > max); // Repeat until valid input is received

		return input; // Return the validated input integer
	}
	else {
		std::cout << "INVALID MIN AND MAX VALUES" << std::endl; //Infroms the user of the code error. this should not theoretically happen but will ensure the robustness of the function.
		std::cout << "Quitting..." << std::endl; // Notify the user
		exit(1); // Exit the program
	}
}

bool Common::validateNumericInput(int& userInput, int lower, int upper) {
    double raw; // Variable to store the raw input as a double
    std::cin >> raw; // Read the input from the user and store it in 'raw'

    // Check if input is invalid: either input failure, out of range, or not an integer
    if (std::cin.fail() || (raw < lower) || (raw > upper) || (std::trunc(raw) != raw)) {
        std::cout << "Invalid input! "; // Display error message for invalid input

        // Provide specific error message based on the nature of the invalid input
        if (std::cin.fail())
            std::cout << "Not numeric." << std::endl; // If input failed
        else if (std::trunc(raw) != raw)
            std::cout << "Not an integer." << std::endl; // If input is not an integer
        else
            std::cout << "Out of range." << std::endl; // If input is out of specified range

        std::cin.clear(); // Clear the error flags
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore the rest of the input line
        return false; // Return false to indicate invalid input
    }

    userInput = static_cast<int>(raw); // Convert the valid input to an integer and store it in 'userInput'
    return true; // Return true to indicate valid input

}
std::string Common::getUserInputStringTwoChoices(std::string prompt, std::string c1, std::string c2) {
    std::string userInput; // Variable to store user input

    do {
        std::cout << prompt; // Prompt the user for input
        std::cin >> userInput; // Read input from the user

        // Check if user wants to quit
        if (userInput == "q" || userInput == "Q") {
            std::cout << "Quitting..." << std::endl;
            exit(1); // Exit the program
        }

        // Check for invalid input
        if ((userInput != c1 && userInput != c2) || std::cin.fail()) {
            std::cin.clear(); // Clear error flags
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore rest of the input line
            std::cout << "Invalid input\nInput must be '" << c1 << "' or '" << c2 << "' and must be a string\nTry again ('q' to quit): ";
        }
    } while ((userInput != c1 && userInput != c2) || std::cin.fail() || userInput == "q" || userInput == "Q"); // Repeat until valid input is received

    return userInput; // Return the valid user input
}
void Common::clearScreen() {
	system("cls");  //clears the screen
}