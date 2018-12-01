#ifndef __SILO_OR_REFINERY_H__
#define __SILO_OR_REFINERY_H__

#include "Building.h"

class SiloOrRefinery : public Building {
    private:
    int especia{};
    int capacity;

    public:
    SiloOrRefinery(Player& player, int id, const std::string& name, int health, const Point& size, int capacity);

    bool tryToStoreSome(int& especia);

    ~SiloOrRefinery();
};

#endif
