#ifndef HUMAN_H_
#define HUMAN_H_

#include <queue>
#include <locale>
#include <string>
#include "Player.h"
#include "Common.h"
#include "Fortification.h"
#include "Reinforcement.h"
#include "Attack.h"


class Human : public Player {
private:
    bool verifyTargetCountry(Country*, Country*);
public:
    Human();
    Human(std::string);
    void reinforce(Map*, Deck*);
    void attack(Map*, Deck*);
    void fortify(Map*, Deck*);
    int defensiveDice(int);
};

#endif