#ifndef CONTINENT_H_
#define CONTINENT_H_

#include <vector>
#include <string>
#include "Country.h"


class Country;
//prevent circular dependency


class Continent {
private:
    int worth;
    std::string name;
    std::vector<Country*> countries;
public:
    Continent(int);
    Continent(int, std::string);
    Continent(int, std::string, std::vector<Country*>);

    void addCountry(Country*);
    std::vector<Country*> getCountries();
    std::string getName();
    int getWorth();
    std::string getOwner();
};

#endif