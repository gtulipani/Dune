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
    return mat.at(tile) == ESPECIA;
}

std::map<unsigned int, Especia*> Map::generateEspeciaFromId(unsigned int& id) {
    std::vector<Point> points = mat.getPointsWith(ESPECIA);
    std::map<unsigned int, Especia*> _especias;
    for (Point p : points) {
        especias[p] = new Especia(id, p);
        _especias[id] = especias.at(p);
        id++;
    }
    return _especias;
}

Point Map::findClosestRefineria(const Point& p) const {
    // Perform a BFS
    return {0, 0};
}

Especia* Map::getEspeciaAt(const Point& pos) {
    return especias.at(pos);
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
            positions.push_back(ady);
            if (positions.size() >= n) return positions;
        }
    }
    return positions;
}
