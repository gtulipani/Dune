#ifndef __TERRAIN_H__
#define __TERRAIN_H__

#include "Point.h"
#include "Matrix.h"

#define TILE_PIXEL_RATE 10

class Terrain {
private:
    Matrix mat;

public:
    Terrain() = default;

    explicit Terrain(Matrix);

    Point findClosest(Point& p) const;

    std::vector<Point> getAdyacents(Point& p) const;

    int getCost(Point& a, Point& b) const;
    Matrix& getMatrix();
};

#endif
