#ifndef ATTACK_H_
#define ATTACK_H_
//header gaurds

#include "Player.h"            // Include necessary header files
#include "Deck.h"
#include "Phase.h"


class Player;
class Deck;
class Phase;
//prevent circular dependency

class Attack {           // Define the Attack class inheriting from Phase

private:
    int numberOfCountriesConquered;     // Variable to track the number of countries conquered
    int id;                             // ID of the attacking player

    void updateAttack();                // Method to update available attack options
    void attackProcedure();             // Method to execute the attack procedure
    bool isContained(Country*, std::vector<Country*>);   // Method to check if a country is already in a vector
    bool validateNumericInput(int&, int, int);       // Method to validate numeric input within a range
    bool validateSpecNumericInput(int&, std::vector<int>);   // Method to validate specific numeric input
    bool userAttack(Country*, Country*);    // Method to simulate a user attack

    Player* player;                             // Pointer to the attacking player
    Deck* deck;                             // Pointer to the deck of cards
    std::vector<Country*> countries;             // Vector to store the countries owned by the attacking player
    std::vector<Country*> attackBase;            // Vector to store potential attack bases
    std::vector<Country*> attackPossibilities;   // Vector to store potential attack possibilities

public:
    void attackInitalization(Player*, Deck* deck);    // Method to initialize an attack phase
    static void attack(Deck*, Player*, Country*, Country*, int, int);   // Method to execute an attack
    static void notifyObserver(Player*, std::string);      // Method to notify an observer (player) about an attack
};

#endif
