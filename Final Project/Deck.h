#ifndef DECK_H_
#define DECK_H_

#include "Card.h" // Include the declaration of Card class
#include <iostream> // Include input/output stream library
#include <vector> // Include vector library for std::vector

class Deck {
public:
    Deck(int numCountries); // Constructor
    Card Draw(); // Method to draw a card from the deck
    int getNumberCards(); // Method to get the number of cards remaining in the deck

private:
    int numCountries; // Total number of countries
    int numInfantry; // Number of Infantry cards
    int numArtillery; // Number of Artillery cards
    int numCavalry; // Number of Cavalry cards
    std::vector<Card> cards; // Vector to store the cards in the deck
};

#endif
