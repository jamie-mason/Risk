#include "Fortification.h" // Include the declaration of Fortification class


void Fortification::startFortify(Player* player) { // Method to start the fortification phase for a player
    notify(player, "Fortification", ""); // Notify the player to begin fortification
}

void Fortification::fortify(Player* player, Country* sourceCountry, Country* targetCountry, int numOfArmies) {
    // Method to move armies from one country to another during the fortification phase
    if (player == NULL) { // Check if the player is valid
        std::cout << "Invalid player." << std::endl; // Print error message
        return;
    }

    if (sourceCountry == targetCountry) { // Check if source and target countries are the same
        std::cout << "Target country is the same as source country. No need to move armies." << std::endl; // Print message
        return;
    }

    if (numOfArmies < 1) { // Check if the number of armies to move is valid
        std::cout << "Need one or more armies to move." << std::endl; // Print error message
        return;
    }

    if (verifyTargetCountry(player, sourceCountry, targetCountry) && // Check if the target country is valid for fortification
        verifyNumOfArmies(sourceCountry, numOfArmies)) { // Check if the number of armies to move is valid

        // Construct fortification message
        std::string message = "Fortifying " + targetCountry->getName() + "'s " +
            std::to_string(targetCountry->getArmies()) + " army/armies with " +
            std::to_string(numOfArmies) + " of " + sourceCountry->getName() + "'s " +
            std::to_string(sourceCountry->getArmies()) + " armies.";

        notifyObserver(player, message); // Notify the player about the fortification

        // Move armies from source to target country
        sourceCountry->removeArmies(numOfArmies);
        targetCountry->addArmies(numOfArmies);
    }
}

bool Fortification::verifyTargetCountry(Player* player, Country* sourceCountry, Country* targetCountry) {
    // Method to verify if the target country is valid for fortification
    std::vector<Country*> playerCountries = player->getCountries(); // Get the list of countries owned by the player

    // Verify ownership of source and target countries
    if (find(playerCountries.begin(), playerCountries.end(), sourceCountry) == playerCountries.end() ||
        find(playerCountries.begin(), playerCountries.end(), targetCountry) == playerCountries.end()) {
        std::cout << "One of the countries does not belong to the player." << std::endl; // Print error message
        return false;
    }

    // Verify link between source and target countries with BFS
    std::queue<Country*> queue;
    std::vector<Country*> borderingCountries;
    std::map<Country*, bool> visitedCountries;

    // Initialize visitedCountries map
    for (Country* playerCountry : player->getCountries()) {
        visitedCountries.insert({ playerCountry, false });
    }

    queue.push(sourceCountry);

    while (!queue.empty()) {
        Country* currentCountry = queue.front();
        queue.pop();
        visitedCountries[currentCountry] = true;

        if (currentCountry == targetCountry)
            return true;

        borderingCountries = currentCountry->getBorderingCountries();

        // Check bordering countries for valid path
        for (Country* borderingCountry : borderingCountries) {
            if (borderingCountry->getOwner() == player && !visitedCountries[borderingCountry])
                queue.push(borderingCountry);
        }
    }

    std::cout << "No path found between countries." << std::endl; // Print error message

    return false;
}

bool Fortification::verifyNumOfArmies(Country* sourceCountry, int numOfArmies) {
    // Method to verify if the number of armies to move is valid
    int sourceCountryNumOfArmies = sourceCountry->getArmies(); // Get the number of armies in the source country

    if (sourceCountryNumOfArmies - numOfArmies < 1) {
        std::cout << "Not enough armies to move." << std::endl; // Print error message
        return false;
    }

    return true;
}

void Fortification::notifyObserver(Player* player, std::string message) {
    notify(player, "Fortification", message); // Notify the player about the fortification
}
