#pragma once
#include "Country.h"

class Continent{
private:
	std::string name;
	int bonusArmies;
	std::vector<Country*> countries;

public:

	Continent();
	Continent(std::string name, int bonusArmies);
	std::string getName() const;
	int getBonusArmies() const;
	void addCountry(Country* country);
	std::vector<Country*>& getCountries();

};