#ifndef __TERRAIN_H__
#define __TERRAIN_H__

#include "Point.h"
#include "Matrix.h"

#define ARENA 0
#define DUNAS 1
#define ROCA 2
#define CIMAS 3
#define PRECIPICIOS 4
#define ESPECIA 5
#define EDIFICIO 6

#define TILE_SIZE 10

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
