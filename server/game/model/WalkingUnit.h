#ifndef __WALKING_UNIT_H__
#define __WALKING_UNIT_H__

#include "IGameObject.h"

#include <stack>
#include "Point.h"
#include <Tick.h>

class Terrain;

class WalkingUnit : public IGameObject {
    unsigned int ticksPerStep;
    unsigned int counter;
    std::stack<Point> path;
    Terrain &terrain;
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
    WalkingUnit(Terrain& terrain, Point& initialPixelPosition, unsigned int movespeed);

    virtual void tick() override;

    void goTo(Point& _pixelGoal);

    bool haveYouChanged() override;

    std::string getState() override;

    Point getPixelPosition() const;

    static unsigned int maxspeed() { // Returns maxspeed for walking units.
        return TICKS_PER_SECOND;
    }
};

#endif
