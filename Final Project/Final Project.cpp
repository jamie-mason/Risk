#include "MapLoader.h"
#include <iostream>
#include <stdexcept>
#include <time.h>
#include "Initialization.h"
#include "Startup.h"
#include "MainLoop.h"
#include "Human.h"
#include <filesystem>

int main(int argc, char* argv[])
{

    Player* human = new Human();
    Player* h2 = new Human();
    std::vector<Player*> players;
    players.push_back(human);
    players.push_back(h2);
    Map* currMap;
    Deck* currDeck;
    std::cout << "File is :" << argv[0];

   Initialization ini(false);
    currMap = ini.getMap();
    currDeck = ini.getDeck();

    for (int i = 0; i < currMap->getCountries().size(); i++) {
        Country* currCountry = currMap->getCountries()[i];
        currCountry->addArmies(1);

        if (i % 2 == 0) {
            currCountry->setOwner(human);
            human->addCountry(currCountry);
        }
        else {
            currCountry->setOwner(h2);
            h2->addCountry(currCountry);
        }
    }
    MainLoop mainLoop(players, currMap, currDeck, 0);
    std::cout << "The winner is: " << mainLoop.playSeveral() << std::endl;
    return 0;
}


