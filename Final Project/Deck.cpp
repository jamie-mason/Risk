#include "Deck.h" // Include the declaration of Deck class

Deck::Deck(int numCountries) { // Constructor definition for Deck class, takes number of countries as argument
    int d = 3; // Define the divisor for distributing card types
    numInfantry = numCountries / 3; // Calculate number of Infantry cards
    numArtillery = numCountries / 3; // Calculate number of Artillery cards
    numCavalry = numCountries / 3; // Calculate number of Cavalry cards
    this->numCountries = numArtillery + numArtillery + numCavalry; // Total number of cards in the deck
    int random; // Variable to store random number

    int maxInf = numInfantry; // Initialize maximum Infantry cards
    int maxArt = numArtillery; // Initialize maximum Artillery cards
    int maxCavalry = numCavalry; // Initialize maximum Cavalry cards
    for (int i = 0; i < this->numCountries; i++) { // Loop to populate the deck with cards
        // set the type of card randomly
        random = rand() % d; // Generate a random number between 0 and 2
        if (random == 0 && maxInf > 0) { // If random number is 0 and there are remaining Infantry cards
            cards.push_back(Card(Card::Infantry)); // Add an Infantry card to the deck
            maxInf--; // Decrement remaining Infantry cards
        }
        else if (random == 1 && maxArt > 0) { // If random number is 1 and there are remaining Artillery cards
            cards.push_back(Card(Card::Artillery)); // Add an Artillery card to the deck
            maxArt--; // Decrement remaining Artillery cards
        }
        else if (random == 2 && maxCavalry > 0) { // If random number is 2 and there are remaining Cavalry cards
            cards.push_back(Card(Card::Cavalry)); // Add a Cavalry card to the deck
            maxCavalry--; // Decrement remaining Cavalry cards
        }
        else {
            i--; // If none of the conditions are met, repeat the loop iteration
        }
    }
}

Card Deck::Draw() { // Method to draw a card from the deck
    if (!cards.empty()) { // Check if the deck is not empty
        Card draw = cards.back(); // Get the top card from the deck
        cards.pop_back(); // Remove the top card from the deck
        Card::cardType type = draw.getCardValue(); // Get the type of the drawn card

        if (type == Card::Infantry) { // If the drawn card is Infantry
            numInfantry--; // Decrement the count of Infantry cards
        }
        else if (type == Card::Artillery) { // If the drawn card is Artillery
            numArtillery--; // Decrement the count of Artillery cards
        }
        else { // If the drawn card is Cavalry
            numCavalry--; // Decrement the count of Cavalry cards
        }

        return draw; // Return the drawn card
    }
    else {
        std::cout << "The deck is empty" << std::endl; // Print error message if the deck is empty
    }
    exit(EXIT_FAILURE); // Exit the program with failure status if the deck is empty
}

int Deck::getNumberCards() { // Method to get the number of cards remaining in the deck
    return cards.size(); // Return the size of the deck (number of cards remaining)
}
