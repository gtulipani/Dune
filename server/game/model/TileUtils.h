#ifndef __TILE_UTILS_H__
#define __TILE_UTILS_H__

#include "Point.h"

class TileUtils {
    unsigned int tileSize;
    unsigned int mapRows;
    unsigned int mapCols;

    public:
    Point getTileFromPixel(Point& pixel) const;

    Point getPixelFromTile(Point& tile) const;
};

#endif