#include "Human.h" //include the contents of the human header file

Human::Human() : Player() {
    //do something
}

Human::Human(std::string n) : Player(n) {
    //do something
}

void Human::reinforce(Map* currMap, Deck* currDeck) {
    // Execute player reinforcement phase
    Reinforcement::executePlayerReinforcement(this, currMap->getContinents());
}

void Human::attack(Map* currMap, Deck* currDeck) {
    // Initialize and execute attack phase
    Attack a;
    a.attackInitalization(this, currDeck);
}


void Human::fortify(Map* currMap, Deck* currDeck) {
    bool good = false; // Flag to track input validity
    int input; // Variable to store user input
    int armies = 0; // Variable to store the number of armies to be moved

    // Display header for fortification options
    std::cout << "Input Index|Country Name|Armies|Enemies Around\n" << std::endl;
    // Get all countries owned by the player
    std::vector<Country*> allCountries = getCountries();
    std::vector<Country*> base; // Stores countries that can be fortified

    // Get all countries that can be fortified
    for (int j = 0; j < allCountries.size(); j++) {
        if (allCountries[j]->getArmies() > 1) {
            for (int i = 0; i < allCountries.size(); i++) {
                // Check if the target country can be fortified from the current country
                if (allCountries[i] != allCountries[j] && verifyTargetCountry(allCountries[j], allCountries[i])) {
                    base.push_back(allCountries.at(j)); // Add the country to the list of fortifiable countries
                    break;
                }
            }
        }
    }

    if (base.empty()) { // Check if there are no fortification options
        std::cout << "No Fortification Options." << std::endl;
        return;
    }

    Fortification::startFortify(this); // Start fortification phase

    char doFortify; // Variable to store user choice for fortification
    std::cout << "Do you wish to fortify (y/n)? " << std::endl;
    std::cin >> doFortify;

    if (toupper(doFortify) == 'N') { // Check if the player chooses not to fortify
        return;
    }

    // Update all the surrounding enemies of fortifiable countries
    for (int i = 0; i < base.size(); i++) {
        base[i]->updateInfo(); // Update information about the fortifiable country
        std::cout << i + 1 << "\t|" << base.at(i)->getName() << "|" << base.at(i)->getArmies() << "|" << base.at(i)->getNumEnemiesAround() << std::endl; // Display fortification options
    }

    // Select the source country
    std::cout << "Select a source country" << std::endl;
    do {
        good = Common::validateNumericInput(input, 1, base.size()); // Validate user input for source country
    } while (!good);

    // Select the amount of armies to move
    Country* sourceCountry = base[input - 1]; // Get the selected source country
    good = false;
    std::cout << "Select number of armies to move (1 - " << sourceCountry->getArmies() - 1 << ")" << std::endl;
    do {
        good = Common::validateNumericInput(input, 1, sourceCountry->getArmies() - 1); // Validate user input for number of armies
    } while (!good);

    armies = input; // Store the number of armies to move
    base.clear(); // Clear the list of fortifiable countries

    // Get all the connected countries
    for (int j = 0; j < allCountries.size(); j++) {
        if (verifyTargetCountry(sourceCountry, allCountries[j]) && sourceCountry != allCountries[j]) {
            base.push_back(allCountries[j]); // Add connected countries to the list
        }
    }

    // Update all connected countries information
    for (int i = 0; i < base.size(); i++) {
        base[i]->updateInfo(); // Update information about connected countries
        std::cout << i + 1 << "\t|" << base.at(i)->getName() << "|" << base.at(i)->getArmies() << "|" << base.at(i)->getNumEnemiesAround() << std::endl; // Display connected countries
    }

    std::cout << "Select a target country" << std::endl;
    good = false;
    do {
        good = Common::validateNumericInput(input, 1, base.size()); // Validate user input for target country
    } while (!good);

    Country* targetCountry = base[input - 1]; // Get the selected target country
    std::cout << sourceCountry->getName() << std::endl; // Display source country name
    std::cout << targetCountry->getName() << std::endl; // Display target country name
    Fortification::fortify(this, sourceCountry, targetCountry, armies); // Perform fortification
}


bool Human::verifyTargetCountry(Country* sourceCountry, Country* targetCountry) {
    // Get the list of countries owned by the player
    std::vector<Country*> playerCountries = getCountries();

    // Initialize variables for BFS
    std::queue<Country*> queue;
    std::vector<Country*> borderingCountries;
    std::map<Country*, bool> visitedCountries;

    // Mark all countries as unvisited
    for (Country* playerCountry : playerCountries) {
        visitedCountries.insert({ playerCountry, false });
    }

    // Start BFS from the source country
    queue.push(sourceCountry);

    while (!queue.empty()) {
        // Process the current country
        Country* currentCountry = queue.front();
        queue.pop();
        visitedCountries[currentCountry] = true;

        // If the target country is found, return true
        if (currentCountry == targetCountry)
            return true;

        // Get the bordering countries of the current country
        borderingCountries = currentCountry->getBorderingCountries();

        // Visit unvisited bordering countries owned by the player
        for (Country* borderingCountry : borderingCountries) {
            if (borderingCountry->getOwner() == this && !visitedCountries[borderingCountry]) {
                queue.push(borderingCountry);
            }
        }
    }

    // Target country not found
    return false;
}


int Human::defensiveDice(int max) {
    // Initialize variables
    bool good = false;
    int input;

    // Prompt defender to select dice
    std::cout << "Defender select dice(1-" << max << "): " << std::endl;

    // Validate input until it is within range
    do {
        good = Common::validateNumericInput(input, 1, max);
    } while (!good);

    // Return the selected number of dice
    return input;
}

