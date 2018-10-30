#include "TileUtils.h"

Point TileUtils::getTileFromPixel(Point& pixel) const {
    return Point(pixel.row / tileSize, pixel.col / tileSize);
}

Point TileUtils::getPixelFromTile(Point& tile) const {
    return Point(tile.row * tileSize, tile.col * tileSize);
}
