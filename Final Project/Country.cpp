#include "Country.h"


Country::Country() {
	owner = "";
	name = "";
	armies = 0;
}
Country::Country(std::string name) {
	this->owner = owner;
	this->name = name;
	this->armies = armies;
}
std::string Country::getName() const {
	return name;
}

void Country::setName(std::string name) {
	this->name = name;
}

std::string Country::getOwner() const {
	return owner;
}

void Country::setOwner(std::string owner) {
	this->owner = owner;
}

int Country::getArmies() const {
	return armies;
}

void Country::setArmies(int armies) {
	this->armies = armies;
}
void Country::addArmies(int numArmies) {
	armies += numArmies;
 }

void Country::removeArmies(int numArmies) {
	armies -= numArmies;
	if (armies < 0) {
		armies = 0;
	}
}
Country::~Country() {
	//If clean up task is needed.
}