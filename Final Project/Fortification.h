#ifndef FORTIFICATION_H_
#define FORTIFICATION_H_

#include "Country.h" // Include the declaration of Country class
#include <iostream> // Include input/output stream library
#include <queue> // Include queue library for std::queue
#include <vector> // Include vector library for std::vector
#include <string> // Include string library for std::string
#include <algorithm> // Include algorithm library for std::find
#include <map> // Include map library for std::map
#include "Phase.h";



class Fortification: public Phase {
public:
    static void startFortify(Player* player); // Method to start the fortification phase for a player
    static void fortify(Player* player, Country* sourceCountry, Country* targetCountry, int numOfArmies); // Method to move armies during fortification phase
    static void notifyObserver(Player* player, std::string message); // Method to notify observer about fortification
    static bool verifyTargetCountry(Player* player, Country* sourceCountry, Country* targetCountry); // Method to verify if the target country is valid for fortification


private:
    static bool verifyNumOfArmies(Country* sourceCountry, int numOfArmies); // Method to verify if the number of armies to move is valid
};

#endif
