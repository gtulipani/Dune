#ifndef __COSECHADORA_H__
#define __COSECHADORA_H__

#include "WalkingUnit.h"

class Especia;
class SiloOrRefinery;

const int ESPECIA_MAX = 200;

typedef enum {
    going,
    collecting,
    returning,
    waiting
} state_t;

class Cosechadora : public WalkingUnit {
    int counter = 0;
    int especia = 0;
    state_t state = waiting;
    Especia* target;
    SiloOrRefinery* store;

    public:
    Cosechadora(Player& player, int id, const std::string& name, int health, const Point& size, const Point& initialPixelPosition,
                Map& map, int movespeed);

    virtual void tick() override;

    virtual void handleRightClick(const Point& pos) override;

    virtual void filterBadTiles(std::vector<Point> &tiles) const override;

    virtual void nextMotion() override;
};

#endif