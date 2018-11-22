#ifndef __MAP_H__
#define __MAP_H__

#include <vector>
#include <map>
#include <Point.h>
#include <TerrainType.h>
#include "Matrix.h"
#include "Player.h"

class Especia;

class Map {
public:
    Matrix mat;
    std::unordered_map<Point, Especia*> especias{};
    std::vector<Point> constructionCenterPositions{};

    Map() = default;

    explicit Map(const Matrix& _matrix);

    void update(TerrainType type, const Point& size, const Point& pos);

    Point findClosestRefineria(const Point& p) const;

    std::vector<Point> getAdyacents(const Point& p) const;

    int getCost(const Point& a, const Point& b) const;

    Matrix& getMatrix();

    std::map<unsigned int, Especia*> generateEspeciaFromId(unsigned int& id);

    bool especiaAt(const Point& pos) const;

    Especia* getEspeciaAt(const Point& pos);
};

#endif
