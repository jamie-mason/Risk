#include "MapLoader.h"
#include <iostream>
#include <stdexcept>

int main()
{
    try {
        MapLoader loader("MapLoaderFileTest.map");
        std::cout << "The Map file was successfully parsed." << std::endl;
    }
    catch (std::invalid_argument e) {
        std::cout << e.what() << std::endl;
    }
	return 0;
}

