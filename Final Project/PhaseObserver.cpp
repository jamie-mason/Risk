#include "PhaseObserver.h" // Include header file for PhaseObserver class

PhaseObserver::PhaseObserver() {
    //empty constry
}
void PhaseObserver::update(Player* newPlayer, std::string newPhase, std::string action) {
    // Check if the player object is valid
    if (newPlayer == NULL) {
        std::cout << "Error: player is null" << std::endl; // Display error message
        return; // Exit the function
    }

    currentPlayer = newPlayer; // Update current player
    currentPhase = newPhase; // Update current phase
    phaseAction = action; // Update phase action

    display(); // Call the display method to show the updated information
}

void PhaseObserver::display() {
    // Display a visual separator
    std::cout << std::endl << "__________________________________________________" << std::endl;
    // Display current player, phase, and action
    std::cout << currentPlayer->getName() + ": " + currentPhase + " phase" << std::endl;
    std::cout << phaseAction << std::endl;
    // Display a visual separator
    std::cout << "__________________________________________________" << std::endl << std::endl;
}

void PhaseObserver::update() {
    // This method is currently empty and not used
}
