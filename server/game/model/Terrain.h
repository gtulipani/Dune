#ifndef __TERRAIN_H__
#define __TERRAIN_H__

#include <Point.h>
#include "Matrix.h"

class Terrain {
private:
    Matrix mat;

public:
    Terrain() = default;

    explicit Terrain(const Matrix& _matrix);

    Point findClosest(const Point& p) const;

    std::vector<Point> getAdyacents(const Point& p) const;

    int getCost(const Point& a, const Point& b) const;

    Matrix& getMatrix();
};

#endif
