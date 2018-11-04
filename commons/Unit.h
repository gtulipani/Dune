#ifndef __UNIT_H__
#define __UNIT_H__

#include <stack>
#include "Point.h"
#include "Terrain.h"
#include "TileUtils.h"

class Unit {
    Terrain &terrain;
    Point pixelPosition;
    Point tilePosition;

    Point pixelGoal;
    std::stack<Point> path;
    //Terrain& t;
    //TileUtils& tileUtils;

    void stepTo(Point& goalPixel);

    public:
    Unit(Terrain& _t, Point initialPixelPosition);

    Unit(const Unit &other);

    Unit(Unit &&other) noexcept;

    // Overloading the assignment by copy
    Unit &operator=(const Unit &other);

    // Overloading the assignment by movement
    Unit &operator=(Unit &&other) noexcept;

    void goTo(Point& pixelGoal);

    void filterBadTiles(std::vector<Point>& tiles) const;

    Point stepAndGetPixelPosition();

    std::stack<Point> getPath() {
        return path;
    }

    ~Unit() = default;
};

std::stack<Point> findPath(Terrain& m, Point& start, Point& goal, Unit& u);

#endif //__UNIT_H_
