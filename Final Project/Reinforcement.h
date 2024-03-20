#ifndef REINFORCEMENT_H_
#define REINFORCEMENT_H_

#include <iostream>
#include <vector>
#include <map>
#include <typeinfo>
#include <sstream>
#include <stdexcept>
#include "Phase.h"
class Reinforcement : public Phase {
private:
	static int calculateCountryBonus(Player*);
	static int calculateContinentBonus(Player*, std::vector<Continent*>);
	static int calculateCardBonus(Player*);
	static int calculateMaxCardBonus(Player*);
public:
	static int staticBonusArmies;
	static void startReinforcementPhase(Player*);
	static void executePlayerReinforcement(Player*, std::vector<Continent*>);
	static void reinforceCountry(Player*, Country*, int);
	static int calculateTotalBonusArmies(Player*, std::vector<Continent*>);
	static void notifyObserver(Player*, std::string);

	static int getUserInputInteger(std::string, int, int);
};



#endif //REINFORCEMENT_H_