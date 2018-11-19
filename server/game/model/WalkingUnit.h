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
    WalkingUnit(Player& player, int id, const Point& size, const Point& initialPosition,
                Map& map, unsigned int movespeed);

    virtual void tick() override;

    virtual void handleRightClick(Player& player, const Point& _pixelGoal) override;

    static unsigned int maxspeed() { // Returns maxspeed for walking picturables_textures_map.
        return TICKS_PER_SECOND;
    }
};

#endif
