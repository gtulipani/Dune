#ifndef __WALKING_UNIT_H__
#define __WALKING_UNIT_H__

#include "GameObject.h"

#include <stack>
#include "Point.h"

class Map;

class WalkingUnit : public GameObject {
    unsigned int ticksPerStep;
    unsigned int counter;
    std::stack<Point> path;
    Map &map;
    Point pixelGoal;
    Point pixelPosition;
    Point tilePosition;

    void checkMovespeed();

    void step();

    void findPath(Point& goal);

    void filterBadTiles(std::vector<Point> &tiles) const;

    void stepTo(Point& goalPixel);

    public:
     // Movespeed on pixels per second.
    WalkingUnit(Map& map, Point& initialPixelPosition, unsigned int movespeed);

    virtual void tick() override;

    void goTo(Point& _pixelGoal);

    Point getPixelPosition() const;

    static unsigned int maxspeed(); // Returns maxspeed for walking units.
};

#endif
