#include "Unit.h"

#define TILE_PIXEL_RATE 10

Unit::Unit(Terrain &_t, Point initialPixelPosition)
        : terrain(_t), pixelPosition(std::move(initialPixelPosition)),
          tilePosition(tile_utils::getTileFromPixel(initialPixelPosition, TILE_PIXEL_RATE)) {}

Unit::Unit(const Unit &other) : Unit(
        other.terrain,
        other.pixelPosition) {}

Unit::Unit(Unit &&other) noexcept : Unit(
        other.terrain,
        std::move(other.pixelPosition)) {}

Unit &Unit::operator=(const Unit &other) {
    if (this == &other) {
        return *this; // other is myself!
    }

    // Copy values
    this->terrain = other.terrain;
    this->pixelPosition = other.pixelPosition;

    return *this;
}

Unit &Unit::operator=(Unit &&other) noexcept {
    if (this == &other) {
        return *this; // other is myself!
    }

    // Copy values
    this->terrain = other.terrain;
    this->pixelPosition = std::move(other.pixelPosition);

    return *this;
}

void Unit::goTo(Point &_pixelGoal) {
    pixelGoal = _pixelGoal;
    Point goalTile = tile_utils::getTileFromPixel(pixelGoal, TILE_PIXEL_RATE);
    path = findPath(terrain, tilePosition, goalTile, *this);
}

void Unit::stepTo(Point &pixel) {
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
        Point &nextTile = path.top();
        if (nextTile == tile_utils::getTileFromPixel(pixelGoal, TILE_PIXEL_RATE)) {
            /*  Si el proximo tile es la meta final (o sea path tiene un solo
                elemento), va directamente. Esto es para no ir al centro de un
                tile y volver si el pixel estaba mas atras. */
            stepTo(pixelGoal);
            if (tilePosition != tile_utils::getTileFromPixel(pixelPosition, TILE_PIXEL_RATE)) {
                /*  Si cambie de tile, estoy en el goal. Debo actualizar mi tile
                    position y hacer pop(). path queda vacio, lugo va
                    directamente. */
                tilePosition = tile_utils::getTileFromPixel(pixelPosition, TILE_PIXEL_RATE);
                path.pop();
            }
        } else {
            /* Si el proximo no es la meta final, debo ir al centro del tile. */
            Point goalPixel = tile_utils::getPixelFromTile(nextTile, TILE_PIXEL_RATE);
            stepTo(goalPixel);
            if (tilePosition != tile_utils::getTileFromPixel(pixelPosition, TILE_PIXEL_RATE)) {
                /* Si cambie de tile, debo actualizar mi tile position. */
                tilePosition = tile_utils::getTileFromPixel(pixelPosition, TILE_PIXEL_RATE);
                /*  Solo hago el pop() cuando llegue al centro, para asegurarme
                    de llegar a el. */
                if (pixelPosition == goalPixel) path.pop();
            }
        }
    }

    return pixelPosition;
}

void Unit::filterBadTiles(std::vector<Point> &tiles) const {}
