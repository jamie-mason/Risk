#ifndef DICEROLLINGPLACE_H_
#define DICEROLLINGPLACE_H_

#include "Dice.h" // Include the declaration of Dice class
#include <iostream> // Include input/output stream library
#include <vector> // Include vector library for std::vector

class DiceRollingPlace {
public:
    DiceRollingPlace(); // Constructor
    void registerResult(int result); // Method to register the result of a dice roll
    std::vector<int> throwDice(int numOfDie); // Method to roll a specified number of dice

private:
    int diceRollHistory[6]; // Array to store the count of each dice roll result
};

#endif
