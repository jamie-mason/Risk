#ifndef MAINLOOP_H
#define MAINLOOP_H

#include "Player.h"
#include "Subject.h"
#include "GameStatsObserver.h"

class GameStatsObserver;
class Player;
class Map;

class MainLoop: public Subject {
private:
    GameStatsObserver* gameStatsObserver;

    std::vector<Player*> playerOrder;
    Map* currentMap;
    Deck* currentDeck;
    int turn;
    int turnsPerPlayer;
    Player* getWinner();
    int maxNumTurns;
    void clearScreen();

public:
    MainLoop(std::vector<Player*>, Map*, Deck*);
    MainLoop(std::vector<Player*>, Map*, Deck*, int);
    std::vector<Player*> getPlayers()const;
    void play();
    int getTurn() const;
    int playSeveral();
    void notify();
    Map* getMap() const;
};












#endif // MAINLOOP_H