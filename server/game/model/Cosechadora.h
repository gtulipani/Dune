#ifndef __COSECHADORA_H__
#define __COSECHADORA_H__

#include "WalkingUnit.h"

const unsigned int COSECHADORA_MOVESPEED = 10;
const Point COSECHADORA_SIZE(32, 32);
const unsigned int TICKS_PER_UNIT_COLLECTED = 20;
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
    Point target;

    public:
    Cosechadora(int id, const Point& initialPosition, Map& map);

    virtual void tick() override;

    virtual void handleRightClick(const Point& pos) override;
};

#endif