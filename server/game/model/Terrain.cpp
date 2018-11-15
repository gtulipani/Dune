#include "Terrain.h"

Terrain::Terrain(Matrix mat) : mat(std::move(mat)) {}

/*  Obviamente, esta funcion solo sirve para probar A*, hay que cambiarla   *
 *  despues, ya que si es adyacente o no depende de mas cosas, y la matriz  *
 *  de terreno, no va a ser solo 1 o 0.                                     *
*/
std::vector<Point> Terrain::getAdyacents(Point& p) const {
    std::vector<Point> ady;
    if (p.row > 0) {
        if (mat.at(p.row - 1, p.col) != 1) {
            ady.push_back(Point(p.row - 1, p.col));
        }
        if (p.col > 0) {
            if (mat.at(p.row - 1, p.col - 1) != 1) {
                ady.push_back(Point(p.row - 1, p.col - 1));
            }
        }
        if (p.col < mat.cols() - 1) {
            if (mat.at(p.row - 1, p.col + 1) != 1) {
                ady.push_back(Point(p.row - 1, p.col + 1));
            }
        }
    }
    if (p.row < mat.rows() - 1) {
        if (mat.at(p.row + 1, p.col) != 1) {
            ady.push_back(Point(p.row + 1, p.col));
        }
        if (p.col > 0) {
            if (mat.at(p.row + 1, p.col - 1) != 1) {
                ady.push_back(Point(p.row + 1, p.col - 1));
            }
        }
        if (p.col < mat.cols() - 1) {
            if (mat.at(p.row + 1, p.col + 1) != 1) {
                ady.push_back(Point(p.row + 1, p.col + 1));
            }
        }
    }
    if (p.col > 0) {
        if (mat.at(p.row, p.col - 1) != 1) {
            ady.push_back(Point(p.row, p.col - 1));
        }
    }
    if (p.col < mat.cols() - 1) {
        if (mat.at(p.row, p.col + 1) != 1) {
            ady.push_back(Point(p.row, p.col + 1));
        }
    }
    return ady;
}

int Terrain::getCost(Point& a, Point& b) const {
    return 0;
}


/*  Debe devolver p si el terreno esta disponible para la unidad, o la ubicacion
    mas cercana disponible para esa unidad. */
Point Terrain::findClosest(Point& p) const {
    return p;
}

Matrix& Terrain::getMatrix() {
    return mat;
}
