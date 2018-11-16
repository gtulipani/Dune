#ifndef __WALKING_UNIT_H__
#define __WALKING_UNIT_H__

#include "GameObject.h"

#include <stack>
#include "Point.h"
#include <Tick.h>

class Map;

class WalkingUnit : public GameObject {
    private:
    unsigned int ticksPerStep;
    unsigned int counter;
    std::stack<Point> path;
    Point tilePosition;

    void checkMovespeed();

    void step();

    void findPath(const Point& goal);

    void filterBadTiles(std::vector<Point> &tiles) const;

    void stepTo(const Point& goalPixel);

    protected:
    Map &map;
    Point pixelGoal;

    public:
     // Movespeed on pixels per second.
    WalkingUnit(int id, const Point& size, const Point& initialPosition,
                Map& map, unsigned int movespeed);

    virtual void tick() override;

    void handleRightClick(const Point& _pixelGoal) override;

    static unsigned int maxspeed() { // Returns maxspeed for walking units.
        return TICKS_PER_SECOND;
    }
};

#endif
