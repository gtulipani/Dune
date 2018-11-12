#ifndef __TILE_UTILS_H__
#define __TILE_UTILS_H__

#include "Point.h"

#define TILE_PIXEL_RATE 10

namespace tile_utils {
    Point getTileFromPixel(Point pixel);
    Point getPixelFromTile(Point tile);
}

#endif