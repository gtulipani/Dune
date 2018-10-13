#ifndef PATH_FINDER_H
#define PATH_FINDER_H

#include <string>
#include <stack>
#include <map>
#include "Matrix.h"
#include "Terrain.h"
#include "Unit.h"

class compare {
    std::map<std::string, int>& priorityMap;

    public:
    explicit compare(std::map<std::string, int>& _priorityMap);

    void set(Point p, int priority);

    bool operator() (const Point& a, const Point& b) const;
};

class PathFinder {
    compare comp;
    std::map<std::string, int> priorityMap;

    public:
    PathFinder();

    std::stack<Point> getPath(Terrain& t, Point start, Point goal, Unit u);
};

#endif
