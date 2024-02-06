#pragma once
#include "IncludedDirectories.h"

class Country {
private:
	std::string name;
	std::string owner;
	int armies;


public:
	Country();
	Country(std::string name);
	std::string getName() const;
	void setName(std::string name);
	std::string getOwner() const;
	void setOwner(std::string owner);
	int getArmies() const;
	void setArmies(int armies);
	void addArmies(int numArmies);
	void removeArmies(int numArmies);
	~Country();
};