#ifndef __TERRAIN_H__
#define __TERRAIN_H__

#include "Point.h"
#include "Matrix.h"

#define ARENA 0
#define DUNAS 1
#define ROCA 2
#define CIMAS 3
#define PRECIPICIOS 4
#define EDIFICIO 5

#define TILE_SIZE 10

class Terrain {
    Matrix mat;

    public:
    Terrain(Matrix& _mat);

    Point findClosest(Point& p) const;

    std::vector<Point> getAdyacents(Point& p) const;

    int getCost(Point& a, Point& b) const;
};

#endif
