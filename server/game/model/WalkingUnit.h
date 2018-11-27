#ifndef __WALKING_UNIT_H__
#define __WALKING_UNIT_H__

#include "SelectableGameObject.h"

#include <stack>
#include "Point.h"
#include <Tick.h>

class Map;

class WalkingUnit : public SelectableGameObject {
    private:
    unsigned int ticksPerStep;
    unsigned int counter = 0;
    protected:
    std::stack<Point> path{};
    Point tilePosition;

    void checkMovespeed();

    void step();

    void findPath(const Point& goal);

    void stepTo(const Point& goalPixel);

    protected:
    Map &map;
    Point pixelGoal;

    public:
    // Movespeed on pixels per second.
    WalkingUnit(Player& player, int id, Sprites sprite, int health, const Point& size, const Point& initialPixelPosition,
                Map& map, unsigned int movespeed);

    virtual void tick() override;

    virtual void handleRightClick(const Point& pos) override;

    static unsigned int maxspeed() { // Returns maxspeed for walking picturables_textures_map.
        return TICKS_PER_SECOND;
    }

    virtual void filterBadTiles(std::vector<Point> &tiles) const = 0;
};

#endif
