#ifndef PLAYER_H_
#define PLAYER_H_

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
#include "Country.h"
#include "Continent.h"
#include "Map.h"
#include "Hand.h"
#include "Card.h"
#include "Deck.h"
#include "Attack.h"
#include "DiceRollingPlace.h"

class Country;
class Continent;
class Deck;
class Map; 
class Attack;
//prevent circular dependency


class Player {

private:
	std::string name;
	int unplaced_armies;
	static int nextID;
	int id;
	std::vector<Country*> countries;
	std::vector<Country*> attackBase;
	std::vector<Country*> attackPossibilities;
	DiceRollingPlace* dices;
	Hand* hand;

public:
	Player();
	~Player();
	Player(std::string);
	Player(std::string, std::vector<Country*>);

	std::string getName();
	int getArmies();
	int getPlacedArmies();
	int getID();
	Hand* getHand();
	DiceRollingPlace* getDicePlace();
	std::vector<Country*> getCountries();
	void addArmies(int newArmies);
	void addCountry(Country* c);
	void removeCountry(Country* c);
	void addArmiesToCountry(int, Country*);
	void removeArmiesFromCountry(int, Country*);
	void showCountries();
	std::vector<int> rollDie(int);

	virtual void reinforce(Map*, Deck*) = 0;
	virtual void attack(Map*, Deck*) = 0;
	virtual void fortify(Map*, Deck*) = 0;
	virtual int defensiveDice(int) = 0;
};

#endif