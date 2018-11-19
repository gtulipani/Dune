#ifndef __TILE_UTILS_H__
#define __TILE_UTILS_H__

#include "Point.h"

#define TILE_PIXEL_RATE 30

namespace tile_utils {
    Point getTileFromPixel(const Point& pixel);
    Point getTileTopLeft(const Point& tile);
    Point getTileCenter(const Point& tile);
}

#endif