#include "Map.h"

#include <queue>
#include <unordered_set>
#include <TileUtils.h>
#include <TerrainType.h>
#include "Especia.h"

Map::Map(const Matrix& mat) : mat(std::move(mat)) {}

/*  Obviamente, esta funcion solo sirve para probar A*, hay que cambiarla   *
 *  despues, ya que si es adyacente o no depende de mas cosas, y la matriz  *
 *  de terreno, no va a ser solo 1 o 0.                                     *
*/
std::vector<Point> Map::getAdyacents(const Point& p) const {
    std::vector<Point> ady;
    if (p.row > 0) {
        if (mat.at(p.row - 1, p.col) == '0') {
            ady.push_back(Point(p.row - 1, p.col));
        }
        if (p.col > 0) {
            if (mat.at(p.row - 1, p.col - 1) == '0') {
                ady.push_back(Point(p.row - 1, p.col - 1));
            }
        }
        if (p.col < mat.cols() - 1) {
            if (mat.at(p.row - 1, p.col + 1) == '0') {
                ady.push_back(Point(p.row - 1, p.col + 1));
            }
        }
    }
    if (p.row < mat.rows() - 1) {
        if (mat.at(p.row + 1, p.col) == '0') {
            ady.push_back(Point(p.row + 1, p.col));
        }
        if (p.col > 0) {
            if (mat.at(p.row + 1, p.col - 1) == '0') {
                ady.push_back(Point(p.row + 1, p.col - 1));
            }
        }
        if (p.col < mat.cols() - 1) {
            if (mat.at(p.row + 1, p.col + 1) == '0') {
                ady.push_back(Point(p.row + 1, p.col + 1));
            }
        }
    }
    if (p.col > 0) {
        if (mat.at(p.row, p.col - 1) == '0') {
            ady.push_back(Point(p.row, p.col - 1));
        }
    }
    if (p.col < mat.cols() - 1) {
        if (mat.at(p.row, p.col + 1) == '0') {
            ady.push_back(Point(p.row, p.col + 1));
        }
    }
    return ady;
}

int Map::getCost(const Point& a, const Point& b) const {
    return 0;
}

void Map::update(TerrainType type, const Point& size, const Point& pos) {
    for (int row = pos.row; row < pos.row + size.row; row++) {
        for (int col = pos.col; col < pos.col + size.col; col++) {
            mat.at(row, col) = type;
        }
    }
}

Matrix& Map::getMatrix() {
    return mat;
}

bool Map::especiaAt(const Point& pos) const {
    Point tile = tile_utils::getTileFromPixel(pos);
    return especias.find(tile) != especias.end();
}

std::map<int, Especia*> Map::generateEspeciaFromId(int& id) {
    std::map<int, Especia*> id_especias_map;
    for (Point p : especia_positions) {
        especias[p] = id_especias_map[id] = new Especia(id, p);
        id++;
    }
    return id_especias_map;
}

Point Map::findClosestRefineria(const Point& p) const {
    return {0, 0};
}

Especia* Map::getEspeciaAt(const Point& pos) {
    Point tile = tile_utils::getTileFromPixel(pos);
    return especias.at(tile);
}

Point Map::getClosestAvailablePoint(const Point& pixelStart, const Point& pixelGoal) {
    Point tileGoal = tile_utils::getTileFromPixel(pixelGoal);
    if (mat.at(tileGoal) != EDIFICIOS) return pixelGoal;
    int i, j;
    for (i = tileGoal.row; i >= 0 && mat.at(i - 1, tileGoal.col) == EDIFICIOS; i--) {}
    for (j = tileGoal.col; j >= 0 && mat.at(tileGoal.row, j - 1) == EDIFICIOS; j--) {}
    Point buildingTopLeft = {i, j};
    for (i = 0; buildingTopLeft.row + i < mat.rows() && mat.at(buildingTopLeft.row + i, buildingTopLeft.col) == EDIFICIOS; i++) {}
    for (j = 0; buildingTopLeft.col + j < mat.cols() && mat.at(buildingTopLeft.row, buildingTopLeft.col + j) == EDIFICIOS; j++) {}
    Point buildingSize = {i, j};
    buildingTopLeft = {buildingTopLeft.row - 1, buildingTopLeft.col - 1};
    std::vector<Point> buildingFrontier;
    for (i = 0; i <= buildingSize.row + 1; i++) {
        buildingFrontier.emplace_back(buildingTopLeft.row + i, buildingTopLeft.col);
    }
    i--;
    for (j = 1; j <= buildingSize.col + 1; j++) {
        buildingFrontier.emplace_back(buildingTopLeft.row + i, buildingTopLeft.col + j);
    }
    j--;
    i--;
    for (; i >= 0; i--) {
        buildingFrontier.emplace_back(buildingTopLeft.row + i, buildingTopLeft.col + j);
    }
    i++;
    j--;
    for (; j > 0; j--) {
        buildingFrontier.emplace_back(buildingTopLeft.row + i, buildingTopLeft.col + j);
    }
    Point tileStart = tile_utils::getTileFromPixel(pixelStart);
    Point clostestPointOnFrontier = buildingFrontier.front();
    for (const Point& p : buildingFrontier) {
        if (p.hDistanceTo(tileStart) < clostestPointOnFrontier.hDistanceTo(tileStart)) {
            clostestPointOnFrontier = p;
        }
    }
    return tile_utils::getTileCenter(clostestPointOnFrontier);
}

std::vector<Point> Map::getAvailableTilesNear(const Point& tilePos, unsigned int n) {
    /*  ______________________  */
    /* |         BFS          | */
    /* | Breadth First Search | */
    std::vector<Point> positions;
    std::queue<Point> queue;
    std::unordered_set<Point> set;

    set.insert(tilePos);
    queue.push(tilePos);
    Point current;
    while (!queue.empty()) {
        current = queue.front();
        queue.pop();

        for (Point ady : getAdyacents(current)) {
            if (set.find(ady) != set.end()) continue;
            set.insert(ady);
            queue.push(ady);
            if (mat.at(ady) == ARENA) {
                positions.push_back(ady);
                if (positions.size() >= n) return positions;
            }
        }
    }
    return positions;
}
