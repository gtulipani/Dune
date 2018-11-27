#ifndef __COSECHADORA_H__
#define __COSECHADORA_H__

#include "WalkingUnit.h"

class Especia;

const unsigned int ESPECIA_MAX = 200;

typedef enum {
    going,
    collecting,
    returning,
    waiting
} state_t;

class Cosechadora : public WalkingUnit {
    unsigned int counter = 0;
    unsigned int especia = 0;
    state_t state = waiting;
    Especia* target;

    public:
    Cosechadora(Player& player, int id, Sprites sprite, int health, const Point& size, const Point& initialPixelPosition,
                Map& map, unsigned int movespeed);

    virtual void tick() override;

    virtual void handleRightClick(const Point& pos) override;

    virtual void filterBadTiles(std::vector<Point> &tiles) const override;
};

#endif