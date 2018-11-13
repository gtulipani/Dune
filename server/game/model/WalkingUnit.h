#ifndef __WALKING_UNIT_H__
#define __WALKING_UNIT_H__

#include "GameObject.h"

#include <stack>
#include "Point.h"
#include <Tick.h>

class Terrain;

class WalkingUnit : public GameObject {
    unsigned int ticksPerStep;
    unsigned int counter;
    std::stack<Point> path;
    Terrain &terrain;
    Point pixelGoal;
    Point tilePosition;

    void checkMovespeed();

    void step();

    void findPath(Point& goal);

    void filterBadTiles(std::vector<Point> &tiles) const;

    void stepTo(Point& goalPixel);

    public:
     // Movespeed on pixels per second.
    WalkingUnit(int id, int sprite, Point size, Terrain& terrain,
                    Point& initialPixelPosition, unsigned int movespeed);

    virtual void tick() override;

    void handleRightClick(const Point& _pixelGoal) override;

    virtual bool haveYouChanged() const override;

    static unsigned int maxspeed() { // Returns maxspeed for walking units.
        return TICKS_PER_SECOND;
    }
};

#endif
