#ifndef __UNIT_H__
#define __UNIT_H__

#include <stack>
#include "Point.h"
#include "Terrain.h"
#include "TileUtils.h"

class Unit {
    Point tilePosition;
    Point pixelPosition;
    Point pixelGoal;
    Terrain& t;
    TileUtils& tileUtils;
    std::stack<Point> path;


    void stepTo(Point& goalPixel);

    public:
    Unit(Terrain& _t, Point& initialPixelPosition, TileUtils& tileUtils);

    void goTo(Point& pixelGoal);

    void filterBadTiles(std::vector<Point>& tiles) const;

    Point stepAndGetPixelPosition();

    ~Unit();
};

std::stack<Point> findPath(Terrain& t, Point& start, Point& goal, Unit& u);

#endif
