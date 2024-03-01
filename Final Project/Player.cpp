#include "Player.h" // Including the header file for Player class

// Static member initialization
int Player::nextID = 1;

// Default constructor
Player::Player() {
    name = ""; // Initializing name
    id = nextID; // Assigning unique ID
    nextID++; // Incrementing for the next player
    unplaced_armies = 0; // Initializing unplaced armies
    hand = new Hand(5); // Creating a hand with 5 cards
    dices = new DiceRollingPlace(); // Creating a place for rolling dice
}

// Destructor
Player::~Player() {
    delete dices; // Deleting the dice rolling place
    delete hand; // Deleting the hand
}

// Constructor with name parameter
Player::Player(std::string n) {
    name = n; // Assigning name
    id = nextID; // Assigning unique ID
    nextID++; // Incrementing for the next player
    unplaced_armies = 0; // Initializing unplaced armies
    hand = new Hand(5); // Creating a hand with 5 cards
    dices = new DiceRollingPlace(); // Creating a place for rolling dice
}

// Constructor with name and countries parameters
Player::Player(std::string n, std::vector<Country*> c) {
    name = n; // Assigning name
    id = nextID; // Assigning unique ID
    nextID++; // Incrementing for the next player
    unplaced_armies = 0; // Initializing unplaced armies
    hand = new Hand(5); // Creating a hand with 5 cards
    dices = new DiceRollingPlace(); // Creating a place for rolling dice
    countries = c; // Assigning countries
}

// Getter for player name
std::string Player::getName() {
    return name;
}

// Getter for unplaced armies
int Player::getArmies() {
    return unplaced_armies;
}

// Getter for the total number of armies placed on countries
int Player::getPlacedArmies() {
    int placedArmies = 0;
    for (size_t i = 0; i < countries.size(); i++) {
        placedArmies += countries.at(i)->getArmies();
    }
    return placedArmies;
}

// Getter for player's hand
Hand* Player::getHand() {
    return hand;
}

// Getter for player's dice rolling place
DiceRollingPlace* Player::getDicePlace() {
    return dices;
}

// Method to add unplaced armies
void Player::addArmies(int newArmies) {
    unplaced_armies = newArmies;
}

// Getter for player's countries
std::vector<Country*> Player::getCountries() {
    return countries;
}

// Method to add armies to a specific country
void Player::addArmiesToCountry(int n, Country* c) {
    if (n <= unplaced_armies && c->getOwner() == this) {
        c->addArmies(n);
        unplaced_armies -= n;
    }
}

// Method to remove armies from a specific country
void Player::removeArmiesFromCountry(int n, Country* c) {
    if (n <= unplaced_armies && c->getOwner() == this) {
        c->removeArmies(n);
        unplaced_armies += n;
    }
}

// Method to add a country to player's owned countries
void Player::addCountry(Country* c) {
    countries.push_back(c);
}

// Method to remove a country from player's owned countries
void Player::removeCountry(Country* c) {
    for (size_t i = 0; i < countries.size(); i++) {
        if (countries[i] == c) {
            countries.erase(countries.begin() + i);
            break;
        }
    }
}

// Method to roll a specified number of dice
std::vector<int> Player::rollDie(int numDie) {
    std::vector<int> results = dices->throwDice(numDie);
    sort(results.begin(), results.begin() + results.size());
    return results;
}

// Method to display player's countries
void Player::showCountries() {
    std::cout << "**********Player " << id << " Countries**********" << std::endl;
    std::cout << "Country Name|Armies" << std::endl;
    for (size_t i = 0; i < countries.size(); i++) {
        std::cout << countries.at(i)->getName() << "|" << countries.at(i)->getArmies() << std::endl;
    }
}

// Getter for player ID
int Player::getID() {
    return id;
}
