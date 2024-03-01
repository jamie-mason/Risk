#include "DiceRollingPlace.h" // Include the declaration of DiceRollingPlace class
#include <string> // Include string library for std::string

void DiceRollingPlace::registerResult(int result) { // Method to register the result of a dice roll
    diceRollHistory[result - 1]++; // Increment the count of the corresponding dice roll result
}

DiceRollingPlace::DiceRollingPlace() { // Constructor definition for DiceRollingPlace class
    for (int i = 0; i < sizeof(diceRollHistory) / sizeof(diceRollHistory[0]); i++) { // Loop through each element of diceRollHistory array
        diceRollHistory[i] = 0; // Initialize each element to zero
        // Sets all of the values in the dice history to zero as their initial values
    }
}

std::vector<int> DiceRollingPlace::throwDice(int numOfDie) { // Method to roll a specified number of dice
    std::vector<int> results; // Vector to store dice roll results

    if (numOfDie < 1 || numOfDie > 3) { // Check if number of dice is invalid
        std::cout << "Invalid number of die" << std::endl; // Print error message
        return results; // Return empty vector
    }

    while (numOfDie > 0) { // Loop until all dice are rolled
        Dice dice; // Create a Dice object
        int result = dice.roll(); // Roll the dice and get the result
        registerResult(result); // Register the result
        results.push_back(result); // Add the result to the vector
        numOfDie--; // Decrement the number of dice remaining to be rolled
    }

    return results; // Return vector containing dice roll results
}
