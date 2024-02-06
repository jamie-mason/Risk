#include "Continent.h"'


Continent::Continent() {
	name = "";
	bonusArmies = 0;
}

Continent::Continent(std::string name, int bonusArmies) {
	this->name = name;
	this->bonusArmies = bonusArmies;
	
}
void Continent::addCountry(Country* country) {
	countries.emplace_back(country);
}
std::string Continent::getName() const {
    return name;
}

int Continent::getBonusArmies() const {
    return bonusArmies;
}

std::vector<Country*>& Continent::getCountries() {
    return countries;
}

