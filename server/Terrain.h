#ifndef TERRAIN_H
#define TERRAIN_H

#include "Matrix.h"
#include "Unit.h"

#define ARENA 0
#define DUNAS 1
#define ROCA 2
#define CIMAS 3
#define PRECIPICIOS 4
#define EDIFICIO 5

class Terrain {
    Matrix mat;

    public:
    Terrain(Matrix& _mat);

    std::vector<Point> getAdyacents(Point p, Unit u) const;

    int getCost(Point a, Point b, Unit u) const;
};

#endif
