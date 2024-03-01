#include "Continent.h" // Include header file for Continent class

// Constructor to initialize a continent with a worth
Continent::Continent(int w) {
    worth = w; // Set the worth of the continent
}

// Constructor to initialize a continent with a worth and name
Continent::Continent(int w, std::string n) {
    worth = w; // Set the worth of the continent
    name = n; // Set the name of the continent
}

// Constructor to initialize a continent with a worth, name, and countries
Continent::Continent(int w, std::string n, std::vector<Country*> cs) {
    worth = w; // Set the worth of the continent
    name = n; // Set the name of the continent
    countries = cs; // Set the countries in the continent
}

// Function to add a country to the continent
void Continent::addCountry(Country* c) {
    countries.push_back(c); // Add the country to the continent's list of countries
}

// Function to retrieve the countries in the continent
std::vector<Country*> Continent::getCountries() {
    return countries; // Return the list of countries in the continent
}

// Function to retrieve the name of the continent
std::string Continent::getName() {
    return name; // Return the name of the continent
}

// Function to retrieve the worth of the continent
int Continent::getWorth() {
    return worth; // Return the worth of the continent
}

// Function to determine the owner of the continent
std::string Continent::getOwner() {
    std::vector<Player*> countryOwners; // Vector to store owners of countries in the continent

    // Iterate over countries and store their owners
    for (Country* c : countries)
        countryOwners.push_back(c->getOwner());

    // Check if all countries have the same owner
    if (equal(countryOwners.begin() + 1, countryOwners.end(), countryOwners.begin()))
        return countryOwners.front()->getName(); // If all countries have the same owner, return the owner's name
    else
        return "Contested"; // If countries have different owners, return "Contested"
}
