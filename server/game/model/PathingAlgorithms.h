#ifndef __PATHING_ALGORITHMS_H__
#define __PATHING_ALGORITHMS_H__

#include <stack>

class Map;
class WalkingUnit;
class Point;

namespace pathing {
    /*  Given a map and a unit, finds a suitable path from start to goal (in
        pixels) and returns a stack of points (in pixels) for each direction of
        the path */
    std::stack<Point> findPath( const Map& map,
                                const WalkingUnit& unit,
                                const Point& start,
                                const Point& goal);

    Point getNextPosition(  const Point& currentPosition,
                            std::stack<Point>& path);
}

#endif
