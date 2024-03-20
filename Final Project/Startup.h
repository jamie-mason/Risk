#ifndef STARTUP_H_
#define STARTUP_H_


#include <stdexcept>
#include <cstdlib> 
#include <iomanip>
#include "Player.h"

class Startup {
private:
	std::vector<Player*> playerOrder;
	Map* currMap;

	void clearScreen();
	void displayPlayersCountriesAndArmies(Player*);
	int getUserInputInteger(std::string, int, int);

public:
	Startup(std::vector<Player*>, Map*);
	Startup(std::vector<Player*>, Map*, bool);
	void randomPlayerOrder();
	void assignPlayerCountries();
	void assignPlayerArmies();
	void assignArmiesAI();
	std::vector<Player*> getPlayerOrder();
	~Startup();
};




#endif
