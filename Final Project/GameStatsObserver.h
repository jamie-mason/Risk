#pragma once
#include "MainLoop.h"
#include "Observer.h"


class MainLoop;

class GameStatsObserver : public Observer {

private:
	bool locked;

protected:
	MainLoop* mainLoop;

public:
	GameStatsObserver(MainLoop* m);
	~GameStatsObserver();
	void update();
	MainLoop* getMainLoop();
	bool getLock();
	void lock();

};
