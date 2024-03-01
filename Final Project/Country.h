#ifndef COUNTRY_H_
#define COUNTRY_H_

#include <iostream>
#include <string>
#include <vector>
#include "Player.h"


class Player;
//prevent circular dependency


class Country {

private:
	int armies;
	int numEnemiesAround;
	bool canAttack;
	std::string countryName;
	std::string continentName;
	Player* owner;
	std::vector<Country*> borderingCountries;
	std::vector<Country*> borderingEnemies;

public:
	Country();
	Country(std::string);
	Country(std::string, std::string);
	Country(std::string, std::string, Player*);
	Country(std::string, std::string, Player*, int);
	Country(std::string, std::string, Player*, int, std::vector<Country*>);

	int getArmies();
	int getNumEnemiesAround();
	void updateInfo();
	bool getCanAttack();
	std::string getName();
	std::string getContinent();
	Player* getOwner();

	// can only change number of armies and owner
	void addArmies(int);
	void removeArmies(int);
	void setOwner(Player*);
	void setArmies(int);
	void addBorderingCountry(Country*);
	std::vector<Country*> getBorderingCountries();
	std::vector<Country*> getBorderingEnemies();
};

#endif