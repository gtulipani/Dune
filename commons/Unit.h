#ifndef __UNIT_H__
#define __UNIT_H__

#include <stack>
#include "Point.h"
#include "Terrain.h"
#include "TileUtils.h"
#include "Map.h"

class Unit {
    Map &map;
    Point pixelPosition;
    Point tilePosition;

    Point pixelGoal;
    std::stack<Point> path;
    //Terrain& t;
    //TileUtils& tileUtils;

    void stepTo(Point& goalPixel);

    public:
    Unit(Map& _m, Point& initialPixelPosition);

    void goTo(Point& pixelGoal);

    void filterBadTiles(std::vector<Point>& tiles) const;

    Point stepAndGetPixelPosition();

    std::stack<Point> getPath() {
        return path;
    }

    ~Unit() = default;
};

std::stack<Point> findPath(Map& m, Point& start, Point& goal, Unit& u);

#endif //__UNIT_H_
