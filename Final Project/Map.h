#pragma once
#include "Continent.h"
class Map {
private:
	std::string name;
	std::vector<Continent> continents;
	std::vector<Country*> countries;

public:
	Map();
	Map(std::string name);
	std::string getName() const;
	std::vector<Continent>& getContinents();
	std::vector<Country*>& getCountries();
	void setContinents();
	void connectCountries(Country* country1, Country* country2);
	


};