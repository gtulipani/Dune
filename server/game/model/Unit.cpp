#include "Unit.h"

Unit::Unit(Terrain& _t, Point& initialPixelPosition, TileUtils& _tileUtils)
: t(_t), tileUtils(_tileUtils){
    pixelPosition = initialPixelPosition;
    tilePosition = tileUtils.getTileFromPixel(initialPixelPosition);
}

void Unit::goTo(Point& _pixelGoal) {
    pixelGoal = _pixelGoal;
    Point goalTile = tileUtils.getTileFromPixel(pixelGoal);
    path = findPath(t, tilePosition, goalTile, *this);
}

void Unit::stepTo(Point& pixel) {
    int row_dir = pixel.row - pixelPosition.row;
    int col_dir = pixel.col - pixelPosition.col;

    if (row_dir != 0) {
        row_dir = row_dir / std::abs(row_dir);
    }
    if (col_dir != 0) {
        col_dir = col_dir / std::abs(col_dir);
    }

    pixelPosition.row += row_dir;
    pixelPosition.col += col_dir;
}

Point Unit::stepAndGetPixelPosition() {
    if (path.empty()) {
        /*  Si path.empty() quiere decir que esta en el mismo tile que el goal.
            Entonces va directamente (si es que no llego ya). */
        if (pixelGoal != pixelPosition) {
            stepTo(pixelGoal);
        }
    } else {
        /*  Si no, entonces debe fijarse cual es el proximo tile. */
        Point& nextTile = path.top();
        if (nextTile == tileUtils.getTileFromPixel(pixelGoal)) {
            /*  Si el proximo tile es la meta final (o sea path tiene un solo
                elemento), va directamente. Esto es para no ir al centro de un
                tile y volver si el pixel estaba mas atras. */
            stepTo(pixelGoal);
            if (tilePosition != tileUtils.getTileFromPixel(pixelPosition)) {
                /*  Si cambie de tile, estoy en el goal. Debo actualizar mi tile
                    position y hacer pop(). path queda vacio, lugo va
                    directamente. */
                tilePosition = tileUtils.getTileFromPixel(pixelPosition);
                path.pop();
            }
        } else {
            /* Si el proximo no es la meta final, debo ir al centro del tile. */
            Point goalPixel = tileUtils.getPixelFromTile(nextTile);
            stepTo(goalPixel);
            if (tilePosition != tileUtils.getTileFromPixel(pixelPosition)) {
                /* Si cambie de tile, debo actualizar mi tile position. */
                tilePosition = tileUtils.getTileFromPixel(pixelPosition);
                /*  Solo hago el pop() cuando llegue al centro, para asegurarme
                    de llegar a el. */
                if (pixelPosition == goalPixel) path.pop();
            }
        }
    }

    return pixelPosition;
}

void Unit::filterBadTiles(std::vector<Point>& tiles) const {}
