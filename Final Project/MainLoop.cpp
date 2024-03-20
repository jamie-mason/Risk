#include "MainLoop.h"
#include "Common.h"

void MainLoop::clearScreen() {
#ifdef _WIN32
	std::system("cls"); // Clear the console screen on Windows
#else
	// Assume Unix-like system
	std::system("clear"); // Clear the console screen on Unix-like systems
#endif
}

MainLoop::MainLoop(std::vector<Player*> players, Map* theMap, Deck* theDeck) {
	playerOrder = players;
	currentMap = theMap;
	currentDeck = theDeck;
	gameStatsObserver = new GameStatsObserver(this);
	turn = 1;
}

MainLoop::MainLoop(std::vector<Player*> players, Map* theMap, Deck* theDeck,
	int max) {
	playerOrder = players;
	currentMap = theMap;
	currentDeck = theDeck;
	gameStatsObserver = new GameStatsObserver(this);
	turn = 1;
	maxNumTurns = max;
}
Player* MainLoop::getWinner() {
	Player* currentPlayer = currentMap->getCountries()[0]->getOwner();
	int i = 1;

	while (i < currentMap->getCountries().size()) {
		if (currentPlayer != currentMap->getCountries()[i]->getOwner()) {
			return NULL;
		}
		i++;
	}

	return currentPlayer;

}

std::vector<Player*> MainLoop::getPlayers() const{
	return playerOrder;
}


int MainLoop::getTurn() const{
	return turn;
}

void MainLoop::play() { // Begins the definition of the play function
    Player* winner; // Declares a pointer to store the winner of the game
    size_t playingIndex = 0; // Initializes the index of the player currently playing

    // Loop through all players and save their game statistics
    for (Player* p : playerOrder)
        p->saveGameStats(new GameStatsObserver(this));

    // Continuously play the game until a winner is determined
    while ((winner = getWinner()) == NULL) {
        Player* currentPlayer = playerOrder[playingIndex]; // Get the current player
        gameStatsObserver = currentPlayer->getGameStats(); // Get game statistics observer for the current player
        notify(); // Notify all observers of the game state


        // Execute the reinforcement, attack, and fortification phases for the current player
        currentPlayer->reinforce(currentMap, currentDeck);
        currentPlayer->attack(currentMap, currentDeck);
        currentPlayer->fortify(currentMap, currentDeck);

        // Increment turn counter if all players have completed their turns
        if (playingIndex++ == playerOrder.size())
            turn++; // Increment the turn counter
		clearScreen();
        playingIndex %= playerOrder.size(); // Ensure playingIndex wraps around to the beginning if it exceeds the number of players
    }

    std::cout << "Winner: " << winner->getName() << std::endl; // Print the name of the winner
}


int MainLoop::playSeveral() { // Begins the definition of the playSeveral function
	Player* winner; // Declares a pointer to store the winner of the game
	Player* currentPlayer; // Declares a pointer to store the current player
	int i = 0; // Initializes a counter variable for player order
	turnsPerPlayer = 0; // Initializes the number of turns per player to zero

	// Begins a do-while loop to continue playing until a winner is found
	do {
		currentPlayer = playerOrder[i]; // Sets the current player to the player at index i
		notifyAll(); // Notifies all observers of the game state
		currentPlayer->reinforce(currentMap, currentDeck); // Executes the reinforcement phase for the current player
		notifyAll(); // Notifies all observers of the game state
		currentPlayer->attack(currentMap, currentDeck); // Executes the attack phase for the current player
		notifyAll(); // Notifies all observers of the game state
		currentPlayer->fortify(currentMap, currentDeck); // Executes the fortification phase for the current player
		// Checks if a full round of turns has been completed for all players
		if (i % playerOrder.size() == playerOrder.size() - 1) {
			turnsPerPlayer += 1; // Increments the number of turns per player
		}
		// Checks if the maximum number of turns per player has been reached
		if (turnsPerPlayer == maxNumTurns) {
			return -1; // Returns -1 to indicate the game has reached the maximum number of turns without a winner
		}
		clearScreen();
		i = (i + 1) % playerOrder.size(); // Moves to the next player in the player order

	} while ((winner = getWinner()) == NULL); // Continues the loop until a winner is found

	return winner->getID(); // Returns the ID of the winning player
}


void MainLoop::notify() {
	gameStatsObserver->update();
}

Map* MainLoop::getMap() const{
	return currentMap;
}