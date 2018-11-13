#include "TileUtils.h"

namespace tile_utils {
    Point getTileFromPixel(const Point& pixel) {
        return {pixel.row / TILE_PIXEL_RATE, pixel.col / TILE_PIXEL_RATE};
    }

    Point getTileTopLeft(const Point& tile) {
        return {tile.row * TILE_PIXEL_RATE, tile.col * TILE_PIXEL_RATE};
    }
    Point getTileCenter(const Point& tile) {
        return {tile.row * TILE_PIXEL_RATE + TILE_PIXEL_RATE / 2,
                tile.col * TILE_PIXEL_RATE + TILE_PIXEL_RATE / 2};
    }

}
