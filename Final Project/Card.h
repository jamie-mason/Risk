#pragma once
#ifndef CARD_H_
#define CARD_H_
#include <iostream>
#include <map>
#include <string>
class Card {
public:
	enum cardType {
		Infantry, Artillery, Cavalry
	};
	Card(cardType);
	Card(cardType, std::string);
	cardType getCardValue();
	void setCardValue(cardType);
	std::string getTerritory();
	void setTerritory(std::string);

private:
	cardType value;
	std::string territory;
	std::map<int, std::string> enumValue;
};
#endif