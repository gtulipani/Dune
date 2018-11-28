#ifndef __WALKING_UNIT_H__
#define __WALKING_UNIT_H__

#include "SelectableGameObject.h"

#include <stack>
#include "Point.h"
#include <Tick.h>
#include <Sprites.h>

class Map;

class WalkingUnit : public SelectableGameObject {
    private:
    int ticksPerStep;
    int counter = 0;

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
    WalkingUnit(Player& player, int id, int type, int health, const Point& size, const Point& initialPixelPosition,
                Map& map, int movespeed);

    virtual void tick() override;

    virtual void handleRightClick(const Point& pos) override;

    virtual void filterBadTiles(std::vector<Point> &tiles) const = 0;

    virtual void nextMotion() = 0;
};

#endif
