#ifndef __TILE_UTILS_H__
#define __TILE_UTILS_H__

#include "Point.h"

namespace tile_utils {
    Point getTileFromPixel(Point& pixel);
    Point getPixelFromTile(Point& tile);
}

#endif