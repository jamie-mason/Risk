#ifndef HAND_H_
#define HAND_H_

#include <iostream>
#include <vector>
#include "Card.h" // Assuming Card class is defined in Card.h



class Hand {
public:
    Hand(int maxCards); // Constructor
    void getCard(Card c); // Add a card to the hand
    void printHand(); // Print the cards in the hand
    int SelectExchange(); // Select cards for exchange
    int getAnyExchange(); // Get any valid exchange
    int getNumberOfCards(); // Get the number of cards in hand

private:
    int maxCards; // Maximum number of cards allowed in the hand
    int numCards; // Current number of cards in the hand
    int exchangeMultiplier; // Multiplier for exchange points
    int exchange; // Number of cards required for exchange
    std::vector<Card> cards; // Vector to store cards in the hand

    bool positionTaken(int position, int exchanges[]); // Check if position is already taken in exchanges
    int verifyInput(int numIteration, int exchanges[]); // Verify user input for exchanging cards
    bool VerifyExchange(int c1, int c2, int c3); // Verify if selected cards are valid for exchange
};

#endif
