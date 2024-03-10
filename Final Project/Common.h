#ifndef COMMON_H_
#define COMMON_H_

#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include "Country.h"
#include "Player.h"

class Common {
public:
    static void displayPlayersCountriesAndArmies(Player*);
    static int getUserInputIntInRange(std::string, int, int);
    static bool validateNumericInput(int&, int, int);
    static std::string getUserInputStringTwoChoices(std::string, std::string, std::string);
    static void clearScreen();
};






#endif