#include "Map.h" // Include header for Map class
#include <deque> // Include header for deque data structure
#include <map> // Include header for map data structure

// Default constructor for Map class
Map::Map() {
}

// Constructor with parameter to initialize Map with a vector of countries
Map::Map(std::vector<Country*> c) {
    countries = c; // Set countries vector
}

// Constructor with parameters to initialize Map with vectors of countries and continents
Map::Map(std::vector<Country*> co, std::vector<Continent*> con) {
    countries = co; // Set countries vector
    continents = con; // Set continents vector
}

// Destructor for Map class
Map::~Map() {
    // Delete dynamically allocated countries
    while (countries.size() > 0) {
        delete countries.back();
        countries.pop_back();
    }

    // Delete dynamically allocated continents
    while (continents.size() > 0) {
        delete continents.back();
        continents.pop_back();
    }
}

// Function to get the vector of countries
std::vector<Country*> Map::getCountries() {
    return countries; // Return countries vector
}

// Function to get the vector of continents
std::vector<Continent*> Map::getContinents() {
    return continents; // Return continents vector
}

// Function to add a country to the map
void Map::addCountry(Country* c) {
    countries.push_back(c); // Add country to countries vector
}

// Function to add a continent to the map
void Map::addContinent(Continent* c) {
    continents.push_back(c); // Add continent to continents vector
}

// Function to verify if all countries are connected
bool Map::verifyCountriesAreConnected() {
    // Use breadth-first search (BFS) to check connectivity of countries
    std::vector<Country*> connectedCountries; // Vector to store connected countries
    std::deque<Country*> countriesToLookAt; // Queue for BFS traversal
    std::map<Country*, bool> visited; // Map to track visited countries
    std::vector<Country*> allCountries = getCountries(); // Get all countries

    // Initialize visited map
    for (int i = 0; i < allCountries.size(); i++) {
        visited.insert(std::pair<Country*, bool>(allCountries[i], false));
    }

    Country* firstCountry = allCountries[0]; // Start BFS from the first country
    connectedCountries.push_back(firstCountry);
    countriesToLookAt.push_back(firstCountry);
    visited[firstCountry] = true;

    // Perform BFS
    while (countriesToLookAt.size() > 0) {
        Country* currentCountry = countriesToLookAt.front();
        countriesToLookAt.pop_front();
        std::vector<Country*> currentBorderingCountries = currentCountry->getBorderingCountries();

        // Check connectivity with bordering countries
        for (int i = 0; i < currentBorderingCountries.size(); i++) {
            Country* bordering = currentBorderingCountries[i];

            if (!visited[bordering]) {
                bool isConnected = false;
                std::vector<Country*> innerBorderingCountries = bordering->getBorderingCountries();

                for (int j = 0; j < innerBorderingCountries.size(); j++) {
                    Country* innerBordering = innerBorderingCountries[j];
                    if (innerBordering == currentCountry) {
                        isConnected = true;
                        break;
                    }
                }

                if (!isConnected) {
                    return false;
                }
                else {
                    connectedCountries.push_back(bordering);
                    countriesToLookAt.push_back(bordering);
                    visited[bordering] = true;
                }
            }
        }
    }

    if (connectedCountries.size() != allCountries.size()) {
        return false;
    }

    return true;
}

// Function to verify if all continents are connected
bool Map::verifyContinentsAreConnected() {
    // Use BFS on each continent to check connectivity
    for (int continentIndex = 0; continentIndex < getContinents().size(); continentIndex++) {
        Continent* currContinent = getContinents()[continentIndex]; // Get current continent

        std::vector<Country*> connectedCountries; // Vector to store connected countries
        std::deque<Country*> countriesToLookAt; // Queue for BFS traversal
        std::map<Country*, bool> visited; // Map to track visited countries
        std::vector<Country*> continentsCountries = currContinent->getCountries(); // Get countries in the continent

        // Initialize visited map
        for (int visitedIndex = 0; visitedIndex < continentsCountries.size(); visitedIndex++) {
            visited.insert(std::pair<Country*, bool>(continentsCountries[visitedIndex], false));
        }

        Country* firstCountry = continentsCountries[0]; // Start BFS from the first country in the continent
        connectedCountries.push_back(firstCountry);
        countriesToLookAt.push_back(firstCountry);
        visited[firstCountry] = true;

        // Perform BFS
        while (countriesToLookAt.size() > 0) {
            Country* currentCountry = countriesToLookAt.front();
            countriesToLookAt.pop_front();
            std::vector<Country*> currentBorderingCountries = currentCountry->getBorderingCountries();

            // Check connectivity with bordering countries in the same continent
            for (int i = 0; i < currentBorderingCountries.size(); i++) {
                Country* bordering = currentBorderingCountries[i];

                if (!visited[bordering] && bordering->getContinent() == currentCountry->getContinent()) {
                    bool isConnected = false;
                    std::vector<Country*> innerBorderingCountries = bordering->getBorderingCountries();

                    for (int j = 0; j < innerBorderingCountries.size(); j++) {
                        Country* innerBordering = innerBorderingCountries[j];
                        if (innerBordering == currentCountry) {
                            isConnected = true;
                            break;
                        }
                    }

                    if (!isConnected) {
                        return false;
                    }
                    else {
                        connectedCountries.push_back(bordering);
                        countriesToLookAt.push_back(bordering);
                        visited[bordering] = true;
                    }
                }
            }
        }

        if (connectedCountries.size() != continentsCountries.size()) {
            return false;
        }
    }

    return true;
}

// Function to verify if countries belong to one continent only
bool Map::verifyCountriesBelongToOneContinent() {
    std::map<std::string, std::string> countryNames; // Map to store country names and their continents

    // Iterate through continents and countries to check continent ownership
    for (int continentIndex = 0; continentIndex < getContinents().size(); continentIndex++) {
        Continent* currContinent = getContinents()[continentIndex]; // Get current continent
        std::vector<Country*> continentsCountries = currContinent->getCountries(); // Get countries in the continent

        // Iterate through countries in the continent
        for (int countryIndex = 0; countryIndex < continentsCountries.size(); countryIndex++) {
            Country* currCountry = continentsCountries[countryIndex]; // Get current country

            // Check if the country name already exists in the map
            if (countryNames.count(currCountry->getName()) > 0) {
                return false; // Country belongs to multiple continents
            }
            else {
                countryNames[currCountry->getName()] = currCountry->getContinent(); // Add country name and continent to map
            }
        }
    }

    return true; // All countries belong to one continent only
}

// Function to verify if the map is valid (all conditions are met)
bool Map::isMapValid() {
    return verifyCountriesBelongToOneContinent() && verifyCountriesAreConnected() && verifyContinentsAreConnected();
}
