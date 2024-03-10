#ifndef MAP_H_
#define MAP_H_

#include <string>
#include <iostream>
#include <vector>
#include "Player.h"
#include "Country.h"
#include "Continent.h"

class Player;
class Continent;
class Country;
//prevent circular dependency


class Map {

private:
	std::vector<Country*> countries;
	std::vector<Continent*> continents;
public:
	Map();
	Map(std::vector<Country*>);
	Map(std::vector<Country*>, std::vector<Continent*>);
	~Map();

	std::vector<Country*> getCountries();
	std::vector<Continent*> getContinents();
	void addCountry(Country*);
	void addContinent(Continent*);
	bool verifyCountriesAreConnected();
	bool verifyContinentsAreConnected();
	bool verifyCountriesBelongToOneContinent();
	bool isMapValid();
};

#endif