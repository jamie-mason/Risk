#include <stdexcept>
#include <iostream>
#include <sstream>
#include "MapLoader.h"
#include <filesystem> // For directory operations


MapLoader::MapLoader() {
    loadedMap = new Map(); // Initialize loadedMap pointer with a new Map object
}

MapLoader::MapLoader(std::string textFileName) {
    loadedMap = new Map(); // Initialize loadedMap pointer with a new Map object
    parseMap(textFileName); // Parse the map from the provided text file
}

MapLoader::~MapLoader() {
    delete loadedMap; // Delete the dynamically allocated Map object to free memory
}

std::string MapLoader::readLine(std::ifstream& fileReader) {
    std::string line;
    if (getline(fileReader, line)) { // Read a line from the file
        if (!line.empty()) {
            return this->strip(line); // Return the stripped line (without '\r' or '\n' characters)
        }
    }
    return ""; // Return an empty string if there are no more lines to read or if line is empty
}

std::string MapLoader::strip(std::string s) {
    while (!s.empty() && (s[s.length() - 1] == '\r' || s[s.length() - 1] == '\n')) {
        s.pop_back(); // Remove the last character ('\r' or '\n') from the string
    }
    return s; // Return the stripped string
}

std::vector<std::string> MapLoader::split(std::string s, char delim) {
    std::stringstream ss(s); // Create a stringstream object with the input string
    std::string input;
    std::vector<std::string> result; // Create a vector to store the split strings

    while (getline(ss, input, delim)) { // Split the stringstream using the delimiter
        result.push_back(input); // Add the split string to the result vector
    }

    return result; // Return the vector of split strings
}

Map* MapLoader::getMap() {
    return loadedMap; // Return the loadedMap pointer
}

void MapLoader::parseMap(std::string textFileName) {
    std::string line;
    std::ifstream fileReader(textFileName); // Open the text file for reading
    if (loadedMap != nullptr) {
        delete loadedMap; // Delete the existing loadedMap to prevent memory leaks
        loadedMap = new Map(); // Create a new Map object
    }

    if ((line = this->readLine(fileReader)) != "[Map]") {
        fileReader.close();
        throw std::invalid_argument("Map file is invalid, missing [Map] section."); // Throw an exception if [Map] section is missing
    }

    while ((line = this->readLine(fileReader)) != "[Continents]" && !fileReader.eof()) {} // Skip lines until [Continents] section

    if (line != "[Continents]") {
        fileReader.close();
        throw std::invalid_argument("Map file is invalid, missing [Continents] section."); // Throw an exception if [Continents] section is missing
    }

    while ((line = this->readLine(fileReader)) != "[Territories]" && !fileReader.eof()) {
        std::vector<std::string> continentInfo = this->split(line, '=');

        if (continentInfo.size() == 2) { // Only parse valid lines with format [continent]=[value]
            Continent* continent;
            try {
                continent = new Continent(stoi(continentInfo[1]), continentInfo[0]); // Create a new Continent object
            }
            catch (std::invalid_argument& e) { // Catch exceptions by reference
                fileReader.close();
                throw std::invalid_argument("Expected integer value for continent but got something else."); // Throw an exception if the continent value is not an integer
            }
            loadedMap->addContinent(continent); // Add the continent to the loaded map
        }
    }

    if (line != "[Territories]") {
        fileReader.close();
        throw std::invalid_argument("Map file is invalid, missing [Territories] section."); // Throw an exception if [Territories] section is missing
    }

    std::vector<std::vector<std::string> > borderingCountries;
    std::map<std::string, bool> countryNames;

    line = this->readLine(fileReader);
    while (!fileReader.eof()) {
        if (line != "") {
            std::vector<std::string> countryInfo = this->split(line, ',');

            if (countryInfo.size() > 4 && countryNames.count(countryInfo[0]) == 0) { // Make sure there are at least 4 fields and the country name did not already show up
                Country* country = new Country(countryInfo[0], countryInfo[3]); // Create a new Country object
                countryNames[country->getName()] = true; // Mark the country name as seen

                bool addedToContinent = false;
                for (size_t i = 0; i < loadedMap->getContinents().size(); i++) {
                    if (loadedMap->getContinents()[i]->getName() == countryInfo[3]) {
                        addedToContinent = true;
                        loadedMap->getContinents()[i]->addCountry(country); // Add the country to the continent
                        break;
                    }
                }

                if (!addedToContinent) {
                    fileReader.close();
                    throw std::invalid_argument("Map file is invalid, continent for country '" + countryInfo[0] + "' does not exist."); // Throw an exception if continent does not exist
                }

                loadedMap->addCountry(country); // Add the country to the loaded map

                std::vector<std::string> bordering;
                for (size_t i = 4; i < countryInfo.size(); i++) {
                    bordering.push_back(countryInfo[i]); // Add the bordering country to the vector
                }
                borderingCountries.push_back(bordering); // Add the vector of bordering countries to the list
            }
            else if (countryInfo.size() <= 4) {
                fileReader.close();
                throw std::invalid_argument("Map file is invalid, missing properties for a territory."); // Throw an exception if territory properties are missing
            }
            else {
                fileReader.close();
                throw std::invalid_argument("Same country cannot show up multiple times in map file."); // Throw an exception if the same country appears multiple times
            }
        }

        line = this->readLine(fileReader); // Read the next line from the file
    }

    for (size_t countryIndex = 0; countryIndex < borderingCountries.size(); countryIndex++) {
        for (size_t borderingCountryIndex = 0; borderingCountryIndex < borderingCountries[countryIndex].size(); borderingCountryIndex++) {
            std::string borderingCountryName = borderingCountries[countryIndex][borderingCountryIndex];

            bool addedBorderingCountry = false;
            for (size_t allCountriesIndex = 0; allCountriesIndex < loadedMap->getCountries().size(); allCountriesIndex++) {
                if (loadedMap->getCountries()[allCountriesIndex]->getName() == borderingCountryName) {
                    addedBorderingCountry = true;
                    loadedMap->getCountries()[countryIndex]->addBorderingCountry(loadedMap->getCountries()[allCountriesIndex]); // Add the bordering country
                    break;
                }
            }

            if (!addedBorderingCountry) {
                fileReader.close();
                throw std::invalid_argument("Map file is invalid, bordering country '" + borderingCountryName + "' for country '" + loadedMap->getCountries()[countryIndex]->getName() + "' does not exist"); // Throw an exception if bordering country does not exist
            }
        }
    }

    if (!loadedMap->isMapValid()) { // Check if the loaded map is valid
        if (!loadedMap->verifyCountriesBelongToOneContinent()) { // Check if countries belong to one continent
            fileReader.close();
            throw std::invalid_argument("Some continents own multiple countries."); // Throw an exception if continents own multiple countries
        }
        else if (!loadedMap->verifyContinentsAreConnected()) { // Check if continents are connected
            fileReader.close();
            throw std::invalid_argument("Some of the continents are not subgraphs, verify that every continent is connected."); // Throw an exception if continents are not connected
        }
        else {
            fileReader.close();
            throw std::invalid_argument("Some of the countries are not connected, this means the map is disjoint when it should not be."); // Throw an exception if countries are not connected
        }
    }

    fileReader.close(); // Close the file stream
}
