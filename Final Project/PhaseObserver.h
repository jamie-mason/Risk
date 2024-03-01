#ifndef PHASEOBSERVER_H_
#define PHASEOBSERVER_H_

#include <iostream>
#include "Observer.h"
#include "Player.h"


class Observer;
class Player;
//prevent circular dependency

class PhaseObserver : public Observer {

private:
	Player* currentPlayer;
	std::string currentPhase;
	std::string phaseAction;

public:
	PhaseObserver();
	void update();
	void update(Player*, std::string , std::string);
	void display();

};

#endif 