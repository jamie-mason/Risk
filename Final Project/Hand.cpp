#include "Hand.h" // Include the declaration of Hand class
#include <algorithm> // Include algorithm library for std::swap
#include <math.h> // Include math library for mathematical functions

Hand::Hand(int maxCards) { // Constructor definition for Hand class, takes maximum cards as argument
	this->maxCards = maxCards; // Assign the maximum cards
	numCards = 0; // Initialize number of cards to 0
	exchangeMultiplier = 0; // Initialize exchange multiplier to 0
	exchange = 3; // Initialize exchange count to 3
}
void Hand::getCard(Card c) { // Method to add a card to the hand, takes a Card object as argument
	cards.push_back(c); // Add the card to the vector of cards
	numCards++; // Increment the number of cards
}

void Hand::printHand() { // Method to print the cards in the hand
	std::cout << "\nCurrent Hand" << std::endl; // Print header for hand
	std::cout << "************" << std::endl; // Print separator line
	for (int i = 0; i < maxCards; i++) { // Loop through each card slot
		if (!cards.empty() && i < cards.size()) { // Check if card slot is not empty and within bounds
			Card::cardType t; // Declare a variable to store card type
			t = cards.at(i).getCardValue(); // Get the card type
			std::string type; // Declare a string to represent the card type
			if (t == Card::Infantry) // Check if card type is Infantry
				type = "Infantry"; // Assign string representation
			if (t == Card::Artillery) // Check if card type is Artillery
				type = "Artillary"; // Assign string representation
			if (t == Card::Cavalry) // Check if card type is Cavalry
				type = "Cavalry"; // Assign string representation
			std::cout << "Card Slot " << i + 1 << ": " << type << std::endl; // Print card slot and type
		}
		else {
			std::cout << "Card Slot " << i + 1 << ": Empty Slot" << std::endl; // Print empty card slot
		}
	}
}

bool Hand::positionTaken(int position, int exchanges[]) { // Method to check if position is already taken in exchanges
	for (int i = 0; i < exchange; i++) { // Loop through exchanges array
		if (exchanges[i] == position) // Check if position matches any existing exchange
			return false; // Return false indicating position is taken
	}
	return true; // Return true indicating position is available
}

int Hand::getNumberOfCards() { // Method to get the number of cards in hand
	return cards.size(); // Return the size of the cards vector
}

// if true, units will be given to player in the main driver
int Hand::verifyInput(int numIteration, int exchanges[]) { // Method to verify user input for exchanging cards
	bool notGood = true; // Flag to indicate invalid input
	double raw, fractpart, intpart; // Variables to store user input and its parts
	int input; // Variable to store converted input
	do {
		std::cout << "Select Card " << numIteration << ": "; // Prompt user to select a card
		if (std::cin >> raw) { // Check if input is numeric
			fractpart = modf(raw, &intpart); // Separate integer and fractional parts
			input = (int)intpart; // Convert to integer
			if (fractpart != 0) { // Check if input is not an integer
				std::cout << "Invalid Input! Number not integer" << std::endl; // Print error message
				continue; // Continue to next iteration of loop
			}
			else if (input < 1 || input > maxCards) { // Check if input is out of range
				std::cout << "Invalid Input! Number out of range" << std::endl; // Print error message
			}
			else if (!positionTaken(input, exchanges)) { // Check if position is already taken
				std::cout << "Invalid Input! Number already selected" << std::endl; // Print error message
			}
			else {
				for (int i = 0; i < exchange; ++i) { // Loop through exchanges array
					if (exchanges[i] == -1) { // Find an empty slot for exchange
						exchanges[i] = input; // Assign input to exchanges array
						break; // Exit loop
					}
				}
				notGood = false; // Set flag to indicate valid input
			}
		}
		else {
			std::cout << "Invalid Input! Number not numeric" << std::endl; // Print error message
			// reset failbit
			std::cin.clear(); // Clear failbit from input stream
			// skip bad input
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore invalid input
		}
	} while (notGood); // Continue loop until valid input is received
	return input; // Return validated input
}

int Hand::SelectExchange() { // Method to select cards for exchange
	int exchanges[3] = { -1, -1, -1 }; // Initialize array to store selected cards for exchange
	int card1;
	int card2;
	int card3;
	printHand(); // Print the current hand
	if (numCards >= 3) { // Check if there are enough cards for exchange
		std::cout << "Select the three cards you wish to exchange" << std::endl; // Prompt user to select cards
		card1 = verifyInput(1, exchanges); // Verify and get first card for exchange
		card2 = verifyInput(2, exchanges); // Verify and get second card for exchange
		card3 = verifyInput(3, exchanges); // Verify and get third card for exchange
		if (VerifyExchange(card1, card2, card3)) { // Check if selected cards are valid for exchange
			if (card2 < card3) // Ensure card2 is greater than card3
				std::swap(card2, card3); // Swap card2 and card3 if necessary
			if (card1 < card2) // Ensure card1 is greater than card2
				std::swap(card1, card2); // Swap card1 and card2 if necessary
			if (card2 < card3) // Ensure card2 is greater than card3
				std::swap(card2, card3); // Swap card2 and card3 if necessary
			cards.erase(cards.begin() + card1 - 1); // Remove card1 from hand
			cards.erase(cards.begin() + card2 - 1); // Remove card2 from hand
			cards.erase(cards.begin() + card3 - 1); // Remove card3 from hand
			std::cout << "Successful exchange." << std::endl; // Print success message
			exchangeMultiplier++; // Increment exchange multiplier
		}
		else {
			std::cout << "Invalid exchange." << std::endl;
		}
	}
	else
		std::cout << "Not enough cards in hand to exchange" << std::endl;
	return 0;
	}
bool Hand::VerifyExchange(int c1, int c2, int c3) {
	// Retrieve the card types for the specified card indexes
	Card::cardType type1 = cards.at(c1 - 1).getCardValue(); // Get card type for first card index
	Card::cardType type2 = cards.at(c2 - 1).getCardValue(); // Get card type for second card index
	Card::cardType type3 = cards.at(c3 - 1).getCardValue(); // Get card type for third card index

	// Check if all card types are the same or all different
	if (type1 == type2 && type2 == type3) {
		return true; // Return true if all are the same
	}
	if (type1 != type2 && type1 != type3 && type2 != type3) {
		return true; // Return true if all are different
	}
	return false; // Otherwise, return false
}

// Gets any exchanges prioritizing unique exchanges over same card types
int Hand::getAnyExchange() {
	// Vector to store indexes of each card type
	std::vector<std::vector<int>> indexes;
	bool validExchangeFound = false;

	// Initialize vector of indexes for each card type
	for (int i = 0; i < 3; i++) {
		std::vector<int> temp;
		indexes.push_back(temp);
	}

	// Populate indexes with the indexes of each card type
	for (int i = 0; i < getNumberOfCards(); i++) {
		indexes[cards[i].getCardValue()].push_back(i);

		// Check for unique exchange
		if (indexes[0].size() >= 1 && indexes[1].size() >= 1 && indexes[2].size() >= 1) {
			if (VerifyExchange(indexes[0][0] + 1, indexes[1][0] + 1, indexes[2][0] + 1)) {
				// Perform exchange if valid and update indexes
				if (indexes[1][0] < indexes[2][0]) std::swap(indexes[1][0], indexes[2][0]); // Swap indexes to ensure proper deletion order
				if (indexes[0][0] < indexes[1][0]) std::swap(indexes[0][0], indexes[1][0]); // Swap indexes to ensure proper deletion order
				if (indexes[1][0] < indexes[2][0]) std::swap(indexes[1][0], indexes[2][0]); // Swap indexes to ensure proper deletion order
				cards.erase(cards.begin() + indexes[0][0]); // Erase first card of the exchange
				cards.erase(cards.begin() + indexes[1][0]); // Erase second card of the exchange
				cards.erase(cards.begin() + indexes[2][0]); // Erase third card of the exchange
				validExchangeFound = true; // Set flag indicating a valid exchange was found
				break; // Exit the loop after performing the exchange
			}
		}
		else if (indexes[cards[i].getCardValue()].size() >= 3) {
			// Check for same card type exchange
			int cardVal = cards[i].getCardValue(); // Get card type for the current card
			if (VerifyExchange(indexes[cardVal][0] + 1, indexes[cardVal][1] + 1, indexes[cardVal][2] + 1)) {
				// Perform exchange if valid and update indexes
				if (indexes[cardVal][1] < indexes[cardVal][2]) std::swap(indexes[cardVal][1], indexes[cardVal][2]); // Swap indexes to ensure proper deletion order
				if (indexes[cardVal][0] < indexes[cardVal][1]) std::swap(indexes[cardVal][0], indexes[cardVal][1]); // Swap indexes to ensure proper deletion order
				if (indexes[cardVal][1] < indexes[cardVal][2]) std::swap(indexes[cardVal][1], indexes[cardVal][2]); // Swap indexes to ensure proper deletion order
				cards.erase(cards.begin() + indexes[cardVal][0]); // Erase first card of the exchange
				cards.erase(cards.begin() + indexes[cardVal][1]); // Erase second card of the exchange
				cards.erase(cards.begin() + indexes[cardVal][2]); // Erase third card of the exchange
				validExchangeFound = true; // Set flag indicating a valid exchange was found
				break; // Exit the loop after performing the exchange
			}
		}
	}

	// If a valid exchange was found, update exchangeMultiplier and return the exchange value
	if (validExchangeFound) {
		exchangeMultiplier++; // Increment exchange multiplier
		return exchangeMultiplier * 5; // Return exchange value
	}

	// Otherwise, return 0 indicating no valid exchange was found
	return 0; // Return 0
}
