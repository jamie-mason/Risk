#include "GameStatsObserver.h"


GameStatsObserver::GameStatsObserver(MainLoop* mainLoop) {
	this->mainLoop = mainLoop;
	this->mainLoop->addObserver(this);
	locked = false;
}

GameStatsObserver::~GameStatsObserver() {
	if (mainLoop != NULL)
		mainLoop->removeObserver(this);
}

void GameStatsObserver::update() {
	std::cout << "\n###GAME STATISTICS###" << std::endl;
	std::cout << "Turn: " + std::to_string(mainLoop->getTurn()) << std::endl;
	std::cout << "#####################" << std::endl;

}

MainLoop* GameStatsObserver::getMainLoop() {
	return mainLoop;
}

void GameStatsObserver::lock() {
	locked = true;
}

bool GameStatsObserver::getLock() {
	return locked;
}