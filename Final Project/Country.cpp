#include "Country.h" // Include header for Country class

// Default constructor to initialize a country with 0 armies, no owner, and unable to attack
Country::Country() {
    armies = 0; // Set initial number of armies to 0
    owner = nullptr; // Set initial owner to nullptr
    canAttack = false; // Set initial attack status to false
}

// Constructor to initialize a country with a specified name, 0 armies, no owner, and unable to attack
Country::Country(std::string country) {
    armies = 0; // Set initial number of armies to 0
    countryName = country; // Set the name of the country
    owner = nullptr; // Set initial owner to nullptr
    canAttack = false; // Set initial attack status to false
}

// Constructor to initialize a country with a specified name, continent, 0 armies, no owner, and unable to attack
Country::Country(std::string country, std::string continent) {
    armies = 0; // Set initial number of armies to 0
    countryName = country; // Set the name of the country
    continentName = continent; // Set the name of the continent
    owner = nullptr; // Set initial owner to nullptr
    canAttack = false; // Set initial attack status to false
}

// Constructor to initialize a country with a specified name, continent, owner, 0 armies, and unable to attack
Country::Country(std::string country, std::string continent, Player* player) {
    armies = 0; // Set initial number of armies to 0
    countryName = country; // Set the name of the country
    continentName = continent; // Set the name of the continent
    owner = player; // Set the owner of the country
    canAttack = false; // Set initial attack status to false
}

// Constructor to initialize a country with a specified name, continent, owner, number of armies, and unable to attack
Country::Country(std::string country, std::string continent, Player* player, int armies) {
    this->armies = armies; // Set initial number of armies
    countryName = country; // Set the name of the country
    continentName = continent; // Set the name of the continent
    owner = player; // Set the owner of the country
    canAttack = false; // Set initial attack status to false
}

// Constructor to initialize a country with a specified name, continent, owner, number of armies, bordering countries, and unable to attack
Country::Country(std::string country, std::string continent, Player* player, int army, std::vector<Country*> countries) {
    armies = army; // Set initial number of armies
    countryName = country; // Set the name of the country
    continentName = continent; // Set the name of the continent
    owner = player; // Set the owner of the country
    borderingCountries = countries; // Set the list of bordering countries
    canAttack = false; // Set initial attack status to false
}

// Function to retrieve the number of armies in the country
int Country::getArmies() {
    return armies; // Return the number of armies
}

// Function to retrieve the name of the country
std::string Country::getName() {
    return countryName; // Return the name of the country
}

// Function to retrieve the continent of the country
std::string Country::getContinent() {
    return continentName; // Return the continent of the country
}

// Function to retrieve the owner of the country
Player* Country::getOwner() {
    return owner; // Return the owner of the country
}

// Function to add armies to the country
void Country::addArmies(int army) {
    armies += army; // Increase the number of armies
}

// Function to remove armies from the country
void Country::removeArmies(int army) {
    armies -= army; // Decrease the number of armies
}

// Function to set the owner of the country
void Country::setOwner(Player* player) {
    owner = player; // Set the owner of the country
}

// Function to set the number of armies in the country
void Country::setArmies(int army) {
    armies = army; // Set the number of armies
}

// Function to add a bordering country to the country
void Country::addBorderingCountry(Country* country) {
    borderingCountries.push_back(country); // Add the bordering country to the list
}

// Function to retrieve the list of bordering countries
std::vector<Country*> Country::getBorderingCountries() {
    return borderingCountries; // Return the list of bordering countries
}

// Function to retrieve the list of bordering enemy countries
std::vector<Country*> Country::getBorderingEnemies() {
    updateInfo(); // Update bordering enemy information
    return borderingEnemies; // Return the list of bordering enemy countries
}

// Function to update bordering enemy information
void Country::updateInfo() {
    numEnemiesAround = 0; // Initialize the number of enemy countries around to 0
    borderingEnemies.clear(); // Clear the list of bordering enemy countries
    for (std::size_t i = 0; i < borderingCountries.size(); i++) {
        if (owner->getID() != borderingCountries.at(i)->getOwner()->getID()) {
            numEnemiesAround++; // Increment the number of enemy countries around
            borderingEnemies.push_back(borderingCountries.at(i)); // Add the enemy country to the list
        }
    }
    // Check if the country can attack based on the number of enemies and armies
    if (numEnemiesAround > 0 && armies > 1)
        canAttack = true; // If there are enemies around and enough armies, set canAttack to true
    else
        canAttack = false; // Otherwise, set canAttack to false
}

// Function to retrieve the number of enemy countries around
int Country::getNumEnemiesAround() {
    return numEnemiesAround; // Return the number of enemy countries around
}

// Function to check if the country can attack
bool Country::getCanAttack() {
    return canAttack; // Return whether the country can attack or not
}
