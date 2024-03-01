#include "Card.h" // Include header file for Card class

// Constructor to initialize a card with a value
Card::Card(cardType value) {
    this->value = value; // Set the card value
}

// Constructor to initialize a card with a value and territory
Card::Card(cardType value, std::string territory) {
    this->value = value; // Set the card value
    this->territory = territory; // Set the territory
}

// Getter function to retrieve the card value
Card::cardType Card::getCardValue() {
    return value; // Return the card value
}

// Setter function to set the card value
void Card::setCardValue(cardType value) {
    this->value = value; // Set the card value
}

// Getter function to retrieve the territory associated with the card
std::string Card::getTerritory() {
    return territory; // Return the territory
}

// Setter function to set the territory associated with the card
void Card::setTerritory(std::string territory) {
    this->territory = territory; // Set the territory
}
