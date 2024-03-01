#ifndef MAP_LOADER_H_
#define MAP_LOADER_H_

#include <string>
#include <fstream>
#include "Map.h"


class MapLoader {
private:
    Map* loadedMap;

protected:
    std::string readLine(std::ifstream&);
    std::string strip(std::string);
    std::vector<std::string> split(std::string, char);

public:
    MapLoader();
    MapLoader(std::string);
    ~MapLoader();

    Map* getMap();
    void parseMap(std::string);
};

#endif