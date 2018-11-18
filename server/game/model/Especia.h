#ifndef __ESPECIA_H__
#define __ESPECIA_H__

#include "GameObject.h"

#include <Point.h>

#define INITIAL_ESPECIA 1000

class Especia : public GameObject {
    private:
    unsigned int counter = 0;
    bool hasCollector = false;

    public:
    Especia(Player& player, int id, const Point& initialPosition);

    bool hasEspeciaLeft() const;

    void tryToGetSome(unsigned int& cosechadoraEspecia);

    virtual void tick() override;

    virtual void handleRightClick(Player& player, const Point& pos) override;

    Point getPosition() const;
};

#endif
