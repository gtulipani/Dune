#include "Map.h"

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
    for (int row = pos.row; row <= pos.row + size.row; row++) {
        for (int col = pos.col; col <= pos.col + size.col; col++) {
            mat.at(row, col) = type;
        }
    }
}

/*  Debe devolver p si el terreno esta disponible para la unidad, o la ubicacion
    mas cercana disponible para esa unidad. */
Point Map::findClosest(const Point& p) const {
    return p;
}

Matrix& Map::getMatrix() {
    return mat;
}
