#ifndef __MAP_H__
#define __MAP_H__

#include <vector>
#include <Point.h>
#include "Matrix.h"

class Map {
public:
    Matrix mat;
    std::vector<Point> constructionCenterPositions;

    Map() = default;

    explicit Map(const Matrix& _matrix);

    Point findClosest(const Point& p) const;

    std::vector<Point> getAdyacents(const Point& p) const;

    int getCost(const Point& a, const Point& b) const;

    Matrix& getMatrix();
};

#endif
